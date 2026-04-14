import {
  addTournamentPlayer,
  createMatchRecord,
  createTournament,
  createUser,
  findMatchById,
  findTournamentMatchByMatchId,
  findUserByDisplayName,
  getTournamentById,
  getTournamentMatches,
  getTournamentPlayers,
  linkTournamentMatch,
  updateMatchResult,
  updateTournamentStatus,
} from '../db.js';
import db from '../db.js';
import { notifyUsersTournament, broadcastTournamentNotification } from '../utils/tournamentNotifications.js';
import { auditAuth, auditMatch } from '../utils/auditLog.js';

const ensureFourAliases = (players) => Array.isArray(players) && players.length === 4;

const buildState = (tournament, players, matches) => {
  const aliasByUserId = new Map(players.map((p) => [p.user_id, p.alias]));

  const mappedMatches = matches.map((m) => {
    const stage = m.match_order <= 2 ? 'semifinal' : 'final';
    const status = m.winner_id || m.winner_alias ? 'completed' : 'pending';
    const p1Alias = m.player1_alias || aliasByUserId.get(m.player1_id) || null;
    const p2Alias = m.player2_alias || aliasByUserId.get(m.player2_id) || null;
    const winnerAlias = m.winner_alias || (m.winner_id ? aliasByUserId.get(m.winner_id) : null) || null;

    return {
      match_id: m.id,
      match_order: m.match_order,
      stage,
      status,
      players: [p1Alias, p2Alias],
      winner: winnerAlias,
      score: m.details?.score || null,
    };
  });

  return {
    id: tournament.id,
    status: tournament.status,
    matches: mappedMatches,
  };
};

export default async function tournamentsRoutes(fastify) {
  // POST /tournaments
  fastify.post('/tournaments', {
    preHandler: fastify.authenticate,
    schema: {
      body: {
        type: 'object',
        required: ['players'],
        properties: {
          name: { type: 'string' },
          players: {
            type: 'array',
            minItems: 4,
            maxItems: 4,
            items: { type: 'string', minLength: 1, maxLength: 128 },
          },
        },
      },
    },
  }, async (request, reply) => {
    const { name = null, players } = request.body || {};

    if (!ensureFourAliases(players)) {
      return reply.code(400).send({ error: 'Provide exactly 4 player aliases' });
    }

    const trimmed = players.map((p) => String(p).trim());
    const unique = new Set(trimmed);
    if (unique.size !== 4) {
      return reply.code(400).send({ error: 'Aliases must be unique' });
    }

    const userRows = trimmed.map((alias) => {
      let user = findUserByDisplayName(alias);
      if (!user) {
        const placeholderEmail = `tournament_${Date.now()}_${alias.toLowerCase().replace(/\s+/g, '_')}@local`;
        user = createUser({
          email: placeholderEmail,
          display_name: alias,
          login: alias,
          first_name: alias,
          last_name: 'Tournament Player',
        });
      }
      return user;
    });

    const nowIso = new Date().toISOString();
    const tournament = createTournament({ name, status: 'pending', started_at: null });

    const playerRows = userRows.map((user, idx) =>
      addTournamentPlayer({
        tournament_id: tournament.id,
        user_id: user.id,
        alias: trimmed[idx],
        slot_order: idx + 1,
      })
    );

    const matches = getTournamentMatches(tournament.id);

    auditAuth({
      action: "tournament_create",
      user: { id: Number(request.user?.sub) || null, display_name: request.user?.display_name || null },
      request,
      extra: {
        "tournament.id": tournament.id,
        "tournament.name": name,
        "tournament.players": trimmed,
      }
    });

    const state = buildState(tournament, playerRows, matches);
    return reply.code(201).send(state);
  });

  // GET /tournaments/:id
  fastify.get('/tournaments/:id', {
    preHandler: fastify.authenticate,
  }, async (request, reply) => {
    const id = Number(request.params.id);
    if (Number.isNaN(id)) {
      return reply.code(400).send({ error: 'Invalid tournament id' });
    }

    const tournament = getTournamentById(id);
    if (!tournament) {
      return reply.code(404).send({ error: 'Tournament not found' });
    }

    const players = getTournamentPlayers(id);
    const matches = getTournamentMatches(id);
    const state = buildState(tournament, players, matches);
    return state;
  });

  // POST /tournaments/:id/start
  fastify.post('/tournaments/:id/start', {
    preHandler: fastify.authenticate,
  }, async (request, reply) => {
    const tournamentId = Number(request.params.id);
    
    if (Number.isNaN(tournamentId)) {
      return reply.code(400).send({ error: 'Invalid tournament id' });
    }

    const tournament = getTournamentById(tournamentId);
    if (!tournament) {
      return reply.code(404).send({ error: 'Tournament not found' });
    }

    if (tournament.status === 'running' || tournament.status === 'finished') {
      return reply.code(400).send({ error: 'Tournament already started or finished' });
    }

    const players = getTournamentPlayers(tournamentId);
    if (!players || players.length !== 4) {
      return reply.code(400).send({ error: 'Tournament must have exactly 4 players to start' });
    }

    const [p1, p2, p3, p4] = players;

    try {

      db.prepare('BEGIN').run();

      updateTournamentStatus(tournamentId, {
        status: 'running',
        started_at: new Date().toISOString(),
      });

      db.prepare('DELETE FROM tournament_matches WHERE tournament_id = ?').run(tournamentId);

      const oldMatches = db.prepare(`
        SELECT match_id FROM tournament_matches WHERE tournament_id = ?
      `).all(tournamentId);
      
      for (const { match_id } of oldMatches) {
        db.prepare('DELETE FROM matches WHERE id = ?').run(match_id);
      }

      const semi1Details = JSON.stringify({ 
        round: 1, 
        status: 'pending', 
        type: 'semi-final',
        stage: 'semifinal',
        bracket: 'A'
      });
      
      const semi1Result = db.prepare(`
        INSERT INTO matches (player1_id, player1_alias, player2_id, player2_alias, details)
        VALUES (?, ?, ?, ?, ?)
      `).run(p1.user_id, p1.alias, p2.user_id, p2.alias, semi1Details);
      
      const match1Id = semi1Result.lastInsertRowid;
      
      db.prepare(`
        INSERT INTO tournament_matches (tournament_id, match_id, match_order) 
        VALUES (?, ?, 1)
      `).run(tournamentId, match1Id);

      const semi2Details = JSON.stringify({ 
        round: 1, 
        status: 'pending', 
        type: 'semi-final',
        stage: 'semifinal',
        bracket: 'B'
      });
      
      const semi2Result = db.prepare(`
        INSERT INTO matches (player1_id, player1_alias, player2_id, player2_alias, details)
        VALUES (?, ?, ?, ?, ?)
      `).run(p3.user_id, p3.alias, p4.user_id, p4.alias, semi2Details);
      
      const match2Id = semi2Result.lastInsertRowid;
      
      db.prepare(`
        INSERT INTO tournament_matches (tournament_id, match_id, match_order) 
        VALUES (?, ?, 2)
      `).run(tournamentId, match2Id);

      const finalDetails = JSON.stringify({ 
        round: 2, 
        status: 'scheduled', 
        type: 'final',
        stage: 'final'
      });
      
      const finalResult = db.prepare(`
        INSERT INTO matches (player1_id, player1_alias, player2_id, player2_alias, details)
        VALUES (NULL, NULL, NULL, NULL, ?)
      `).run(finalDetails);
      
      const match3Id = finalResult.lastInsertRowid;
      
      db.prepare(`
        INSERT INTO tournament_matches (tournament_id, match_id, match_order) 
        VALUES (?, ?, 3)
      `).run(tournamentId, match3Id);

      db.prepare('COMMIT').run();

      auditAuth({
        action: "tournament_start",
        user: { id: Number(request.user?.sub) || null, display_name: request.user?.display_name || null },
        request,
        extra: { "tournament.id": tournamentId }
      });

      auditMatch({
        action: "match_created",
        match: { id: match1Id, player1_id: p1.user_id, player2_id: p2.user_id, winner_id: null, details: JSON.parse(semi1Details) },
        extra: {
          "tournament.id": tournamentId,
          "match.stage": "semifinal",
          "match.bracket": "A",
          "match.player1_alias": p1.alias,
          "match.player2_alias": p2.alias,
        }
      });

      auditMatch({
        action: "match_created",
        match: { id: match2Id, player1_id: p3.user_id, player2_id: p4.user_id, winner_id: null, details: JSON.parse(semi2Details) },
        extra: {
          "tournament.id": tournamentId,
          "match.stage": "semifinal",
          "match.bracket": "B",
          "match.player1_alias": p3.alias,
          "match.player2_alias": p4.alias,
        }
      });

      auditMatch({
        action: "match_created",
        match: { id: match3Id, player1_id: null, player2_id: null, winner_id: null, details: JSON.parse(finalDetails) },
        extra: {
          "tournament.id": tournamentId,
          "match.stage": "final",
          "match.bracket": "final",
          "match.player1_alias": null,
          "match.player2_alias": null,
        }
      });

      broadcastTournamentNotification(
        fastify,
        `🏆 Tournament #${tournamentId} has started! Semi-finals are ready.`
      );

      const match1Players = [p1.user_id, p2.user_id].filter(id => id);
      const match2Players = [p3.user_id, p4.user_id].filter(id => id);

      if (match1Players.length > 0) {
        notifyUsersTournament(
          fastify,
          match1Players,
          `🎮 Your semifinal match is ready: ${p1.alias} vs ${p2.alias}`
        );
      }
      
      if (match2Players.length > 0) {
        notifyUsersTournament(
          fastify,
          match2Players,
          `🎮 Your semifinal match is ready: ${p3.alias} vs ${p4.alias}`
        );
      }

      const freshTournament = getTournamentById(tournamentId);
      const freshPlayers = getTournamentPlayers(tournamentId);
      const freshMatches = getTournamentMatches(tournamentId);
      const state = buildState(freshTournament, freshPlayers, freshMatches);
      return state;

    } catch (err) {
      try { db.prepare('ROLLBACK').run(); } catch (_) {}
      console.error("❌ Tournament start failed:", err);
      return reply.code(500).send({ error: 'Failed to start tournament' });
    }
  });

  // POST /tournaments/:id/match
  fastify.post('/tournaments/:id/match', {
    preHandler: fastify.authenticate,
    schema: {
      body: {
        type: 'object',
        required: ['match_id', 'winner'],
        properties: {
          match_id: { type: 'number' },
          winner: { type: 'string' },
          score: {
            type: 'object',
            properties: {
              player1: { type: 'number' },
              player2: { type: 'number' },
            },
          },
        },
      },
    },
  }, async (request, reply) => {
    const tournamentId = Number(request.params.id);
    if (Number.isNaN(tournamentId)) {
      return reply.code(400).send({ error: 'Invalid tournament id' });
    }

    const { match_id, winner, score } = request.body || {};

    const tournament = getTournamentById(tournamentId);
    if (!tournament) {
      return reply.code(404).send({ error: 'Tournament not found' });
    }

    const tmRow = findTournamentMatchByMatchId(tournamentId, match_id);
    if (!tmRow) {
      return reply.code(404).send({ error: 'Match not found in this tournament' });
    }

    const match = findMatchById(match_id);
    if (!match) {
      return reply.code(404).send({ error: 'Match not found' });
    }

    if (match.winner_id || match.winner_alias) {
      console.warn(`⚠️ Attempt to update already completed match ${match_id}. Current winner: ${match.winner_alias}`);
      return reply.code(400).send({ 
        error: 'Match already completed',
        current_winner: match.winner_alias 
      });
    }

    const players = getTournamentPlayers(tournamentId);
    const aliasByUserId = new Map(players.map((p) => [p.user_id, p.alias]));
    const userIdByAlias = new Map(players.map((p) => [String(p.alias).trim(), p.user_id]));

    const winnerId = userIdByAlias.get(String(winner).trim());
    if (!winnerId) {
      return reply.code(400).send({ error: 'Winner alias must belong to tournament players' });
    }

    const stage = tmRow.match_order <= 2 ? 'semifinal' : 'final';
    const winnerAlias = aliasByUserId.get(winnerId) || String(winner).trim();

    const updatedMatch = updateMatchResult(match_id, {
      winner_id: winnerId,
      winner_alias: winnerAlias,
      details: {
        ...match.details,
        stage,
        score: score || match.details?.score || null,
      },
    });

    auditMatch({
      action: "match_completed",
      match: {
        id: updatedMatch.id,
        player1_id: updatedMatch.player1_id,
        player2_id: updatedMatch.player2_id,
        winner_id: updatedMatch.winner_id,
        details: updatedMatch.details,
      },
      extra: {
        "tournament.id": tournamentId,
        "match.stage": stage,
        "match.winner_alias": winnerAlias,
        "match.player1_alias": updatedMatch.player1_alias || aliasByUserId.get(updatedMatch.player1_id) || null,
        "match.player2_alias": updatedMatch.player2_alias || aliasByUserId.get(updatedMatch.player2_id) || null,
        "reported_by.user_id": Number(request.user?.sub) || null,
      }
    });

    const allMatches = getTournamentMatches(tournamentId);

    if (stage === 'semifinal') {
      const semiA = allMatches.find((m) => m.match_order === 1);
      const semiB = allMatches.find((m) => m.match_order === 2);
      const finalMatch = allMatches.find((m) => m.match_order === 3);

      const semiAWinner = semiA?.winner_id || null;
      const semiBWinner = semiB?.winner_id || null;

      if (semiAWinner && semiBWinner) {
        if (!finalMatch) {
          const final = createMatchRecord({
            player1_id: semiAWinner,
            player2_id: semiBWinner,
            player1_alias: aliasByUserId.get(semiAWinner) || null,
            player2_alias: aliasByUserId.get(semiBWinner) || null,
            details: {
              stage: 'final',
            },
          });
          linkTournamentMatch({ tournament_id: tournamentId, match_id: final.id, match_order: 3 });

          auditMatch({
            action: "match_created",
            match: {
              id: final.id,
              player1_id: final.player1_id,
              player2_id: final.player2_id,
              winner_id: null,
              details: final.details
            },
            extra: {
              "tournament.id": tournamentId,
              "match.stage": "final",
              "match.bracket": "final",
              "match.player1_alias": final.player1_alias || null,
              "match.player2_alias": final.player2_alias || null,
            }
          });

          console.log("✅ Final match created with both winners");
        } else if (!finalMatch.player1_id || !finalMatch.player2_id) {
          db.prepare(`UPDATE matches SET player1_id = ?, player2_id = ?, player1_alias = ?, player2_alias = ?, details = ? WHERE id = ?`).run(
            semiAWinner,
            semiBWinner,
            aliasByUserId.get(semiAWinner) || null,
            aliasByUserId.get(semiBWinner) || null,
            JSON.stringify({
              ...(finalMatch.details || {}),
              stage: 'final',
            }),
            finalMatch.id,
          );

          auditMatch({
            action: "final_ready",
            match: {
              id: finalMatch.id,
              player1_id: semiAWinner,
              player2_id: semiBWinner,
              winner_id: null,
              details: finalMatch.details,
            },
            extra: {
              "tournament.id": tournamentId,
              "match.stage": "final",
              "match.bracket": "final",
              "match.player1_alias": aliasByUserId.get(semiAWinner) || null,
              "match.player2_alias": aliasByUserId.get(semiBWinner) || null,
            }
          });

          console.log("✅ Final match updated with both winners:", aliasByUserId.get(semiAWinner), "vs", aliasByUserId.get(semiBWinner));

          const finalists = [semiAWinner, semiBWinner].filter(id => id);
          if (finalists.length > 0) {
            const player1Name = aliasByUserId.get(semiAWinner) || 'Player 1';
            const player2Name = aliasByUserId.get(semiBWinner) || 'Player 2';
            notifyUsersTournament(
              fastify,
              finalists,
              `🏆 Final match ready: ${player1Name} vs ${player2Name}! Get ready to play!`
            );
          }
        } else {
          console.log("⏳ Waiting for both semifinals to complete before updating final");
        }
      }
    }

    if (stage === 'final' && updatedMatch.winner_id) {
      const finishedTournament = updateTournamentStatus(tournamentId, {
        status: 'finished',
        finished_at: new Date().toISOString(),
      });

      auditMatch({
        action: "tournament_finished",
        match: {
          id: updatedMatch.id,
          player1_id: updatedMatch.player1_id,
          player2_id: updatedMatch.player2_id,
          winner_id: updatedMatch.winner_id,
          details: updatedMatch.details,
        },
        extra: {
          "tournament.id": tournamentId,
          "tournament.status": finishedTournament?.status || "finished",
          "tournament.finished_at": finishedTournament?.finished_at || null,
          "tournament.winner_alias": updatedMatch.winner_alias || winnerAlias || null,
        }
      });
    }

    const freshTournament = getTournamentById(tournamentId);
    const freshPlayers = getTournamentPlayers(tournamentId);
    const freshMatches = getTournamentMatches(tournamentId);
    const state = buildState(freshTournament, freshPlayers, freshMatches);
    return state;
  });
}

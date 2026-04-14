import { useNavigate } from "react-router";
import { useState, useContext, useEffect } from "react";
import { GameContext } from "../../context/GameContext";
import { TournamentContext } from "../../context/TournamentContext";
import { useTranslation } from 'react-i18next';

interface User {
	id: number | null;
	login: string | null;
	display_name?: string | null;
	avatar?: string | null;
	alias?: string;
}

interface Tournament {
	id: number;
	name?: string;
	status: string;
	participants: User[];
	matches?: any[];
}

const parseMatchDetails = (match: any) => {
	try {
		const meta = typeof match?.details === 'string' 
			? JSON.parse(match.details) 
			: match?.details || {};
		return {
			round: meta?.round || 1,
			status: meta?.status || 'pending',
			type: meta?.type || 'unknown',
			stage: meta?.stage || match?.stage || 'semifinal',
			bracket: meta?.bracket || null
		};
	} catch (e) {
		console.error('Failed to parse match details:', e);
		return {
			round: 1,
			status: 'pending',
			type: 'unknown',
			stage: match?.stage || 'semifinal',
			bracket: null
		};
	}
};

export default function Tournaments() {
	const game = useContext(GameContext);
	const navigate = useNavigate();
	const tournament = useContext(TournamentContext);
	const { t } = useTranslation();
	const [matches, setMatches] = useState<any[]>([]);
	const [tournamentStatus, setTournamentStatus] = useState<string>('running');
	const [loading, setLoading] = useState(true);
	const [isStarting, setIsStarting] = useState(false);
	const [participants, setParticipants] = useState<User[]>([]);
	
	const startTournament = async () => {
		if (!tournament.id || isStarting) return;
		
		setIsStarting(true);
		try {
			const apiUrl = (import.meta as any).env?.VITE_API_URL || process.env.VITE_API_URL || "/api";
			const response = await fetch(`${apiUrl}/tournaments/${tournament.id}/start`, {
				method: 'POST',
				credentials: 'include',
				headers: { 'Content-Type': 'application/json' },
				body: JSON.stringify({})
			});
			
			if (response.ok) {
				await fetchTournamentState();
			} else {
				const error = await response.json();
				alert(error.error || 'Failed to start tournament');
			}
		} catch (err) {

			alert('Failed to start tournament');
		} finally {
			setIsStarting(false);
		}
	};
	
	const fetchTournamentState = async () => {
		if (!tournament.id) return;
		
		try {
			const apiUrl = (import.meta as any).env?.VITE_API_URL || process.env.VITE_API_URL || "/api";
			const response = await fetch(`${apiUrl}/tournaments/${tournament.id}`, {
				credentials: 'include'
			});
			
			if (response.ok) {
				const data = await response.json();
			
				setParticipants(data.participants || []);
				setMatches(data.matches || []);
				setTournamentStatus(data.status || 'running');
				
				const pendingMatches = data.matches.filter((m: any) => m.status === 'pending');
				const completedMatches = data.matches.filter((m: any) => m.status === 'completed');

				completedMatches.forEach((m: any) => {
					const details = parseMatchDetails(m);
					if (details.stage === 'semifinal') {
						if (m.match_order === 1) tournament.match1_winner = m.winner;
						if (m.match_order === 2) tournament.match2_winner = m.winner;
					}
				});
				
				const finalMatch = data.matches.find((m: any) => {
					const details = parseMatchDetails(m);
					return details.stage === 'final' && m.status === 'completed';
				});
				if (finalMatch) {
					tournament.winner = finalMatch.winner;
				}

				return data;
			}
		} catch (err) {
			console.error('Failed to fetch tournament state:', err);
		} finally {
			setLoading(false);
		}
	};

	const startMatchByOrder = async (order: number) => {
		try {
			if ((order === 1) && matches.length === 0 && tournamentStatus === 'pending') {
				await startTournament();
			}
			const data = await fetchTournamentState();
			const target = (data?.matches || []).find((m: any) => m.match_order === order);
			if (target) {
				if (order === 3) {
					const playersOk = Array.isArray(target.players) && target.players[0] && target.players[1];
					if (!playersOk) {
						console.warn('Final cannot start: finalists not set yet');
						return;
					}
				}
				start(target);
			}
		} catch (e) {
			console.error('Failed to start match by order', order, e);
		}
	};
	
	useEffect(() => {
		if (!tournament.id) {
			navigate("/game/tournaments");
			return;
		}
		
		fetchTournamentState();
		
		if (game.finished) {
			fetchTournamentState();
			game.finished = false; 
		}
	}, [game.finished]);

	const start = (matchData: any) => {
		if (!matchData) return;
		
		if (matchData.status === 'completed') {
			console.warn("⚠️ Cannot start already completed match:", matchData);
			return;
		}

		const details = parseMatchDetails(matchData);
		
		game.left_player.name = matchData.players[0] || "";
		game.right_player.name = matchData.players[1] || "";
		game.left_player.score = 0;
		game.right_player.score = 0;
		game.winner = "";
		game.finished = false;
		game.is_tournament = true;
		game.destination = "/game/tournament_table";

		tournament.match = {
			match_id: matchData.match_id || matchData.id,
			match_order: matchData.match_order,
			stage: details.stage
		};

		try {
			localStorage.setItem("pong.match.ctx", JSON.stringify({
				match_id: matchData.match_id || matchData.id,
				left_player_name: game.left_player.name,
				right_player_name: game.right_player.name,
			}));
		} catch {}
		
		console.log("🎮 Starting match:", matchData.match_order, "Players:", matchData.players);
		navigate("/game/pong");
	};
	if (loading) {
		return <div className="flex h-full w-full items-center justify-center p-6">Loading tournament...</div>;
	}
	
	const semi1 = matches.find(m => m.match_order === 1);
	const semi2 = matches.find(m => m.match_order === 2);
	const final = matches.find(m => m.match_order === 3);

	const semi1Players: (string | null | undefined)[] = (semi1?.players && Array.isArray(semi1.players))
		? semi1.players
		: [
			participants[0]?.alias ?? null,
			participants[1]?.alias ?? null,
		];

	const semi2Players: (string | null | undefined)[] = (semi2?.players && Array.isArray(semi2.players))
		? semi2.players
		: [
			participants[2]?.alias ?? null,
			participants[3]?.alias ?? null,
		];

	const finalPlayers: (string | null | undefined)[] = (final?.players && Array.isArray(final.players)) ? final.players : [null, null];

	const isFinalClickable = Boolean(
		final?.status === 'pending' &&
		Array.isArray(finalPlayers) &&
		finalPlayers[0] && finalPlayers[1]
	);

	const handleWinnerClick = () => {
		if (!tournament.winner || tournament.winner === "—") return;
		try {
			(tournament as any).id = undefined;
			tournament.name = "";
			tournament.players = [] as any;
			tournament.finalPlayers = [] as any;
			tournament.match = null as any;
			tournament.match1_winner = "";
			tournament.match2_winner = "";
			tournament.winner = "";

			game.setGameData(prev => ({
				...prev,
				is_tournament: false,
				destination: "/game/chose",
				left_player: { ...prev.left_player, name: "", score: 0 },
				right_player: { ...prev.right_player, name: "", score: 0 },
				finished: false,
				winner: ""
			}));

			setMatches([]);
			setParticipants([]);
			setTournamentStatus('running');

			navigate("/game/chose");
		} catch (e) {
			console.error('Failed to reset tournament frontend state', e);
			navigate("/game/chose");
		}
	};

	const getPlayerName = (alias: string | null | undefined): string => {
		if (!alias) return "—";

		const participant = participants.find(p => p.alias === alias);
		if (!participant) return alias;

		if (!participant.id) return participant.alias || alias;

		return participant.display_name || participant.login || participant.alias || alias;
	};
	
	return (
		<div className="flex min-h-screen w-full items-center justify-center p-3 sm:p-6">
			<div className="grid w-full max-w-6xl grid-cols-1 gap-3 text-purple-500 border border-purple-500 rounded-2xl p-3 sm:grid-cols-3 sm:grid-rows-7 sm:gap-4 sm:rounded-3xl sm:p-6">
				<div className="col-span-1 flex flex-col gap-3 justify-center items-center p-2 sm:col-span-3 sm:row-span-1">
					<span className="text-lg neon-btn neon-pulse tracking-neon sm:text-2xl">
						{t("menu.tournaments")} {name !== "" && ( ": " + name)}
					</span>

			</div>

				<div className="col-span-1 border border-dashed border-purple-500 rounded-2xl flex justify-center items-center sm:row-span-6 sm:rounded-3xl">
					<div className="grid h-full w-full grid-cols-1 gap-2 text-purple-400 p-2 sm:grid-rows-7 sm:gap-4 sm:p-4">
						<div className="col-span-1 text-purple-400 rounded-2xl flex justify-center items-center text-sm font-semibold py-2 sm:row-span-1 sm:rounded-3xl sm:text-base">Semi-final</div>
						{(() => {
							const isClickable = (semi1?.status === 'pending') || (matches.length === 0 && tournamentStatus === 'pending' && participants.length >= 2);
							const className = isClickable
								? "neon-btn neon-pulse neon-btn-light tracking-neon col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center cursor-pointer min-h-[80px] sm:row-span-3 sm:rounded-3xl sm:min-h-0"
								: "col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center min-h-[80px] sm:row-span-3 sm:rounded-3xl sm:min-h-0";
							return (
								<div 
									onClick={isClickable ? () => startMatchByOrder(1) : () => {}}
									className={className}
								>
							<div className="grid w-full grid-cols-1 grid-rows-2 text-purple-400 gap-2 sm:gap-4">
								<div className="col-span-1 row-span-1 flex justify-center items-center">
								<p className="overflow-hidden mx-2 my-1 text-ellipsis text-sm sm:m-3 sm:text-base">{getPlayerName(semi1Players[0])}</p>
							</div>
							<div className="col-span-1 row-span-1 flex justify-center items-center">
								<p className="overflow-hidden mx-2 my-1 text-ellipsis text-sm sm:m-3 sm:text-base">{getPlayerName(semi1Players[1])}</p>
								</div>
							</div>
							</div>
							);
						})()}
						<div 
							onClick={semi2?.status === 'pending' ? () => startMatchByOrder(2) : () => {}}
							className={semi2?.status === 'pending' ? (
								"neon-btn neon-pulse neon-btn-light tracking-neon col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center cursor-pointer min-h-[80px] sm:row-span-3 sm:rounded-3xl sm:min-h-0"
							) : (
								"col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center min-h-[80px] sm:row-span-3 sm:rounded-3xl sm:min-h-0"
							)}>
							<div className="grid w-full grid-cols-1 grid-rows-2 text-purple-400 gap-2 sm:gap-4">
								<div className="col-span-1 row-span-1 flex justify-center items-center">
								<p className="overflow-hidden mx-2 my-1 text-ellipsis text-sm sm:m-3 sm:text-base">{getPlayerName(semi2Players[0])}</p>
							</div>
							<div className="col-span-1 row-span-1 flex justify-center items-center">
								<p className="overflow-hidden mx-2 my-1 text-ellipsis text-sm sm:m-3 sm:text-base">{getPlayerName(semi2Players[1])}</p>
								</div>
							</div>
						</div>
					</div>
				</div>
				<div className="col-span-1 border border-dashed border-purple-500 rounded-2xl flex justify-center items-center sm:row-span-6 sm:rounded-3xl">
					<div className="grid h-full w-full grid-cols-1 gap-2 text-purple-400 p-2 sm:grid-rows-6 sm:gap-4 sm:p-4">
						<div className="col-span-1 text-purple-400 rounded-2xl flex justify-center items-center text-sm font-semibold py-2 sm:row-span-1 sm:rounded-3xl sm:text-base">Final</div>
						<div className="hidden sm:block col-span-1 row-span-1 rounded-3xl"></div>
						<div 
											onClick={isFinalClickable ? () => startMatchByOrder(3) : () => {}}
											className={isFinalClickable ? (
								"neon-btn neon-pulse neon-btn-light tracking-neon col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center cursor-pointer min-h-[80px] sm:row-span-3 sm:rounded-3xl sm:min-h-0"
							) : (
								"col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center min-h-[80px] sm:row-span-3 sm:rounded-3xl sm:min-h-0"
							)}>
							<div className="grid w-full grid-cols-1 grid-rows-2 text-purple-400 gap-2 sm:gap-4">
								<div className="col-span-1 row-span-1 flex justify-center items-center">
								<p className="overflow-hidden mx-2 my-1 text-ellipsis text-sm sm:m-3 sm:text-base">{getPlayerName(finalPlayers[0])}</p>
							</div>
							<div className="col-span-1 row-span-1 flex justify-center items-center">
								<p className="overflow-hidden mx-2 my-1 text-ellipsis text-sm sm:m-3 sm:text-base">{getPlayerName(finalPlayers[1])}</p>
								</div>
							</div>
						</div>
						<div className="hidden sm:block col-span-1 row-span-1 rounded-3xl"></div>
					</div>
				</div>
				<div className="col-span-1 border border-dashed border-purple-500 rounded-2xl flex justify-center items-center sm:row-span-6 sm:rounded-3xl">
					<div className="grid h-full w-full grid-cols-1 gap-2 text-purple-400 p-2 sm:grid-rows-7 sm:gap-4 sm:p-4">
						<div className="col-span-1 text-purple-400 rounded-2xl flex justify-center items-center text-sm font-semibold py-2 sm:row-span-1 sm:rounded-3xl sm:text-base">Winner</div>
						<div className="hidden sm:block col-span-1 row-span-2 rounded-3xl"></div>
						<div 
							onClick={tournament.winner && tournament.winner !== "—" ? handleWinnerClick : () => {}}
							className={(tournament.winner && tournament.winner !== "—") ? (
								"neon-btn neon-pulse neon-btn-light tracking-neon col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center cursor-pointer min-h-[60px] py-3 sm:row-span-2 sm:rounded-3xl sm:min-h-0 sm:py-0"
							) : (
								"col-span-1 border border-purple-500 rounded-2xl flex justify-center items-center min-h-[60px] py-3 sm:row-span-2 sm:rounded-3xl sm:min-h-0 sm:py-0"
							)}>
							<p className="mx-2 overflow-hidden text-ellipsis text-sm sm:text-base">{getPlayerName(tournament.winner)}</p>
						</div>
						<div className="hidden sm:block col-span-1 row-span-2 rounded-3xl"></div>
					</div>
				</div>
			</div>
		</div>
	);
}

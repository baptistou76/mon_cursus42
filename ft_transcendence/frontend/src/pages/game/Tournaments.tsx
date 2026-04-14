import { Button } from "flowbite-react";
import { Link, useNavigate } from "react-router";
import { useState, useContext, useEffect } from "react";
import { useAuth } from "../../context/AuthContext";
import { useTranslation } from 'react-i18next';
import { TournamentContext } from "../../context/TournamentContext";
import { GameContext } from "../../context/GameContext";

export default function Tournaments() {
	const navigate = useNavigate();
	const { t } = useTranslation();
	const { user, isAuthenticated} = useAuth();
	const game = useContext(GameContext);
	const tournament = useContext(TournamentContext);
	const username = (isAuthenticated && user) ? user.display_name : "";
	const [players, setPlayers] =  useState<string[]>([username, "Alex", "Bill", "Bob"]);
	const [tournamentName, setTournamentName] = useState<string>("");
	const [isCreating, setIsCreating] = useState(false);

	useEffect(() => {
		if (!isAuthenticated) {
			navigate('/game/mode');
		}
	}, [isAuthenticated, navigate]);

	const saveData = async () => {
		if (!isAuthenticated) {
			navigate('/');
			return;
		}
		setIsCreating(true);
		try {
			const idx: number[] = [];
			while (idx.length < players.length) {
				let equal = false;
				let n = Math.floor(Math.random() * players.length);
				for (let i = 0; i < idx.length; ++i) if (n === idx[i]) equal = true;
				if (!equal) idx.push(n);
			}
			const random_players: string[] = idx.map((i) => players[i]);

			const apiUrl = (import.meta as any).env?.VITE_API_URL || process.env.VITE_API_URL || "/api";
			const res = await fetch(`${apiUrl}/tournaments`, {
				method: 'POST',
				headers: { 'Content-Type': 'application/json' },
				credentials: 'include',
				body: JSON.stringify({ name: tournamentName, players: random_players })
			});
			if (!res.ok) {
				console.error('Failed to create tournament', res.status);
				setIsCreating(false);
				return;
			}
			const tournamentData = await res.json();
			tournament.id = tournamentData.id;
			tournament.players = random_players;
			tournament.finalPlayers = ["—", "—"];
			tournament.winner = "—";
			if (tournamentData.matches && tournamentData.matches.length > 0) {
				tournament.match = { match_id: tournamentData.matches[0].match_id };
			}
			game.is_tournament = true;
			game.destination = "/game/tournament_table";
			navigate('/game/tournament_table');
		} catch (err) {
			console.error('Error creating tournament', err);
		} finally {
			setIsCreating(false);
		}
	};

	const addPlayer = () => {
		if (players.length < 4) {
			setPlayers([...players, ""]);
		}
	};
	const removePlayer = (index: number) => {
		if (players.length > 2) {
			setPlayers(players.filter((_, i) => i !== index));
		}
	};

	const updatePlayer = (index: number, value: string) => {
		const newPlayers = [...players];
		newPlayers[index] = value;
		setPlayers(newPlayers);
	};

	const canStart = players.filter((p) => p.trim() !== "").length == 4;

	return (
	<div className="flex flex-col items-center gap-6 p-8">
      <h1 className="text-2xl font-bold tracking-neon">{t("menu.tournaments")}</h1>
		<input
			type="text"
			placeholder={"Tournament1"}
			value={tournamentName}
			onChange={(e) => setTournamentName(e.target.value)}
			className="flex-1 p-3 neon-btn neon-btn-light tracking-neon text-sm rounded-lg"
		/>
      {/* Liste des joueurs */}
      <div className="flex flex-col gap-4 w-full max-w-md">
        {players.map((player, index) => (
          <div key={index} className="flex items-center gap-2">
            <span className="w-8 text-center">{index + 1}.</span>
            <input
              type="text"
              value={player}
              onChange={(e) => updatePlayer(index, e.target.value)}
              placeholder={`Player ${index + 1}`}
              className="flex-1 p-3 neon-btn neon-btn-light tracking-neon text-sm rounded-lg"
            />
            {players.length > 2 && (
              <button
                onClick={() => removePlayer(index)}
                className="w-10 h-10 flex items-center justify-center text-red-500 hover:bg-red-500/20 rounded-lg transition-colors text-xl font-bold"
              >
                −
              </button>
            )}
          </div>
        ))}
      </div>

      {/* Bouton ajouter un joueur */}
      {players.length < 8 && (
        <button
          onClick={addPlayer}
          className="w-12 h-12 flex items-center justify-center neon-btn neon-btn-light rounded-full text-2xl font-bold"
        >
          +
        </button>
      )}

      {/* Info nombre de joueurs */}
      <p className="text-sm opacity-70">
        {players.length} {t("menu.player")}{players.length > 1 ? t("menu.player_s") : ""} ({t("menu.min")} 4, {t("menu.max")} 4)
      </p>

			{/* Bouton démarrer */}
			<div className="flex items-center gap-2">
				<Button
					onClick={saveData}
					disabled={!canStart || isCreating}
					className={`w-48 h-16 neon-btn tracking-neon text-base rounded-lg ${
						(canStart && !isCreating) ? "neon-btn-light" : "neon-btn-light opacity-50 cursor-not-allowed"
					}`}
				>
					{isCreating ? t("menu.creating") || "Creating..." : t("menu.start_tournament")}
				</Button>
			</div>
    </div>
	);
}

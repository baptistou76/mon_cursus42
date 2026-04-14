import { Button } from "flowbite-react";
import { useNavigate} from "react-router";
import { useTranslation } from 'react-i18next';
import { useState, useContext, useEffect } from "react";
import { useAuth } from "../../context/AuthContext";
import { GameContext } from "../../context/GameContext";

export default function ChosePlayer() {
	const { t } = useTranslation();
	const game = useContext(GameContext);
	const { user, isAuthenticated } = useAuth();
	const [ leftPlayer, setLeftPlayer ] = useState("");
	const [ rightPlayer, setRightPlayer ] = useState("");
	const navigate = useNavigate();
	const disable_left = (game.ai_mode === 1 || game.ai_mode === 3);
	const disable_right = (game.ai_mode === 2 || game.ai_mode === 3);

	useEffect(() => {
		setLeftPlayer(disable_left ? "AI Bot" : "");
		setRightPlayer(disable_right ? "AI Bot" : (isAuthenticated && user) ? user.display_name : "");
	}, [isAuthenticated, user, disable_left, disable_right]);
	const canStart = (leftPlayer !== "" && rightPlayer !== "");
	const start = () => {
		game.setGameData({
			ai_mode: game.ai_mode,
			left_player: { ...game.left_player, name: leftPlayer },
			right_player: { ...game.right_player, name: rightPlayer },
			destination: "/game/mode"
		});
		(game.game_type == 1) ? navigate("/game/pong") : navigate("/game/breakout");
	};

	return (
		<div className="grid grid-cols-1 items-center content-stretch gap-4 place-items-center">
			<div className="grid grid-cols-1 md:grid-cols-2 gap-10 m-20">
				<div className="mb-6">
					<input
						disabled={disable_left}
						type="text"
						value={leftPlayer}
						placeholder={leftPlayer === "" ? "Anonymous" : ""}
						onChange={(e) => setLeftPlayer(e.target.value)}
						className="field-sizing-content md:field-sizing-fixed block w-full p-4 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg"
					/>
				</div>
				<div className="mb-6">
					<input
						disabled={disable_right}
						type="text"
						value={rightPlayer}
						placeholder={rightPlayer === "" ? "Anonymous" : ""}
						onChange={(e) => setRightPlayer(e.target.value)}
						className="block w-full p-4 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg"
					/>
				</div>
			</div>
			<div className="items-center mb-6">
				<Button type="button" disabled={!canStart} onClick={start} className="w-48 h-24 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg">{t("menu.start")}</Button>
			</div>
		</div>
	);
}

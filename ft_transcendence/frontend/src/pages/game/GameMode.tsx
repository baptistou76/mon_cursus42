import Btn from "./GameMenuButton.tsx";
import { useTranslation } from 'react-i18next';
import { useContext } from "react";
import { useNavigate } from "react-router";
import { GameContext } from "../../context/GameContext";
import { useAuth } from "../../context/AuthContext";

export default function GameMode() {
	const { t } = useTranslation();
	const navigate = useNavigate();
	const game = useContext(GameContext);
	const { isAuthenticated } = useAuth();

	const local_game = () => {
		game.ai_mode = 0;
		game.left_player.name = "";
		game.right_player.name = "";
		navigate("/game/chose_player");
	};

	const ai_game = () => {
		game.ai_mode = 1;
		game.left_player.name = "AI";
		game.right_player.name = "";
		navigate("/game/chose_player");
	};

	return (
		<div className="grid grid-cols-1 items-center content-stretch gap-4 place-items-center">
			<div className="flex flex-col sm:flex-row gap-6 sm:gap-10 m-10 sm:m-20">
				<Btn onclick={local_game} label={t("menu.local")} />
				<Btn onclick={ai_game} label={t("menu.ai")} />				
				{isAuthenticated && <Btn to="/game/tournaments" label={t("menu.tournaments")} />}
			</div>
		</div>
	);
}


import { Button } from "flowbite-react";
import { Link, useNavigate } from "react-router"; 
import { useContext } from "react";
import { GameContext } from "../../context/GameContext";
import { useTranslation } from "react-i18next";

export default function ChoseGame() {
	const { t } = useTranslation();
	const navigate = useNavigate();
	const game = useContext(GameContext);

	const setGameType = (type) => {
		game.game_type = type;
		game.left_player.name = "";
		game.right_player.name = "";
		game.destination = "/game/chose";
	};
	return (
		<div className="grid grid-cols-1 items-center content-stretch gap-4 place-items-center">
			<div className="grid grid-cols-1 gap-10 m-20">
				<div className="flex flex-col items-center gap-3">
					<p className="text-center text-sm sm:text-base md:text-lg font-semibold text-gray-700 dark:text-gray-300 px-4">
						{t("game.pong.description")}
					</p>
					<Button as={Link} onClick={()=>{ setGameType(1); navigate("/game/mode"); }} className="w-42 h-42 md:w-48 md:h-48  lg:w-52 lg:h-52  xl:w-64 xl:h-64  2xl:w-72 2xl:h-72 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg menu">
						<img src="/pong.svg" alt="Pong game"></img>
					</Button>
				</div>
				<div className="flex flex-col items-center gap-3">
					<p className="text-center text-sm sm:text-base md:text-lg font-semibold text-gray-700 dark:text-gray-300 px-4">
						{t("game.breakout.description")}
					</p>
					<Button  as={Link} onClick={()=>{ setGameType(2); navigate("/game/chose_player"); }} className="w-42 h-42 md:w-48 md:h-48  lg:w-52 lg:h-52  xl:w-64 xl:h-64  2xl:w-72 2xl:h-72 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg">
						<img src="/breakout.svg" alt="Hybrid breakout game"></img>
					</Button>
				</div>
			</div>
		</div>
	);
}

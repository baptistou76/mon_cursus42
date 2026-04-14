import { Button } from "flowbite-react";
import { Link } from "react-router"; 
import { useTranslation } from 'react-i18next';

export default function NewGame() {
	const { t } = useTranslation();	
	var game_type = 1;
	return (
		<div className="grid grid-cols-1 items-center content-stretch gap-4 place-items-center">
			<div className="grid grid-cols-1 md:grid-cols-2 gap-10 m-20">
				<div className="mb-6"><input type="text" placeholder="Player1" className="block w-full p-4 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg"/></div>
				<div className="mb-6"><input type="text" placeholder="Player2" className="block w-full p-4 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg"/></div>
			</div>	
			<div className="items-center mb-6"><Button as={Link} to={game_type ? "/game/pong" : "/game/breakout"} className="w-48 h-24 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg">{t("menu.start")}</Button></div>
		</div>
	  );
}

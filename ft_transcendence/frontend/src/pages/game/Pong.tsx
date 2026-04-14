import Game from "./Game.tsx";
import { useContext } from "react";
import { GameContext } from "../../context/GameContext";

export default function Pong() {
	const game = useContext(GameContext);
	game.game_type = 1;
	return (
		<Game />
	);
}

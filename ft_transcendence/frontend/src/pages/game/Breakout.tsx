import Game from "./Game.tsx";
import { useContext } from "react";
import { GameContext } from "../../context/GameContext";

export default function Breakout() {
	const game = useContext(GameContext);
	game.game_type = 2;
	return (
		<Game />
	);
}
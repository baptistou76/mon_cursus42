import { createContext, useContext, useState } from "react";

type Player = {
	id: number;
	name: string;
	score: number;
}

type GameContextType = {
	game_type: number;
	l_player: Player;
	r_player: Player;
	ai_mode: number; // 0- no AI, 1- left AI, 2- right AI, 3- both are AI
	winner: string;
};

const GameStateContext = createContext<GameContextType>({
	game_type: null;
	l_player: null;
	r_player: null;
	ai_mode: null;
	winner: "";
});

export function GameStateUpdater({ children }:{children: RecordingState.ReactNode}) {
	const [lScore, setLScore] = useState(0);
	const [rScore, setRScore] = useState(0);
	const server = process.env.SERVER_IP || "localhost";
	const game_api = "https://" + server + ":443/game-api/";


	const sendScore = () => {
		fetch(game_api+"/score", {
			method: "POST",
			credentials: "include"
		})
		.then((resp) => {
			console.log("Score sent");
			console.log("Response: "+resp);
			console.log("Response.status: "+resp.status);
			if (resp.ok) console.log("resp.json: "+resp.json);
		})
		.catch((err)=>{
			console.error("Error: "+ err.message);
		});
	};
};

//export default function GameState() {
//  	return (
//	);
//}

export default function GameState() {
	const context = useContext(GameStateContext);
	return context;
}



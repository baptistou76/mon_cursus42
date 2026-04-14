import { createContext, useState, ReactNode } from "react";

type Player = {
	id: number;
	name: string;
	score: number;
};

type GameContextType = {
	game_type: number;
	left_player: Player;
	right_player: Player;
	ai_mode: number;
	is_tournament: boolean;
	finished: boolean;
	winner: string;
	destination: string;
	setGameData: (data: Partial<GameContextType> | ((prev: GameContextType) => GameContextType)) => void;
};

const defaultValues: GameContextType = {
	game_type: 1,
	left_player: { id: -1, name: "", score: 0 },
	right_player: { id: -1, name: "", score: 0 },
	ai_mode: 0,
	is_tournament: false,
	finished: false,
	winner: "",
	destination: "/game/tournaments",
	setGameData: () => {}
};

export const GameContext = createContext<GameContextType>(defaultValues);

export const GameProvider = ({ children }: { children: ReactNode }) => {
	const [gameData, setGameData] = useState<GameContextType>(defaultValues);
	
	// Wrapper для setGameData, поддерживает и объект и функцию
	const updateGameData = (data: Partial<GameContextType> | ((prev: GameContextType) => GameContextType)) => {
		if (typeof data === 'function') {
			setGameData(data);
		} else {
			setGameData(prev => ({ ...prev, ...data }));
		}
	};
	
	// Важно: передаем объект целиком И функцию обновления
	return (
		<GameContext.Provider value={{ ...gameData, setGameData: updateGameData }}>
			{children}
		</GameContext.Provider>
	);
};

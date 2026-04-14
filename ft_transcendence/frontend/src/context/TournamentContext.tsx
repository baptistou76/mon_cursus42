import { createContext } from "react";

export const TournamentContext = createContext({
	name: "",
	players: [],
	finalPlayers: [],
	match: null,
	match1_winner: "",
	match2_winner: "",
	winner: ""
});

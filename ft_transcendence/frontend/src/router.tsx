import { createBrowserRouter } from "react-router";
import Root from "./components/Root.tsx";
import Home from "./pages/Home.tsx";
import Profile from "./pages/Profile.tsx";

import Pong from "./pages/game/Pong.tsx";
import Breakout from "./pages/game/Breakout.tsx";
import GameMode from "./pages/game/GameMode.tsx";
import NewJoin from "./pages/game/NewJoin.tsx";
import NewGame from "./pages/game/NewGame.tsx";
import JoinGame from "./pages/game/JoinGame.tsx";
import ChoseGame from "./pages/game/ChoseGame.tsx";
import ChosePlayer from "./pages/game/ChosePlayer.tsx";
import Tournaments from "./pages/game/Tournaments.tsx";
import TournamentTable from "./pages/game/TournamentTable.tsx";
import Chat from "./pages/Chat.tsx";

import Settings from "./pages/Settings.tsx";
import Friends from "./pages/Friends.tsx";
import NotFound from "./pages/NotFound.tsx";
import Register from "./pages/Register.tsx";

export const router = createBrowserRouter([
	{
		path: "/",
		Component: Root,
		children: [
			{ index: true, Component: Home },
			{ path: "profile", Component: Profile },
			{ path : "profile/:userId", Component: Profile },
			{ path:"game", children: [
				{ index: true, Component: ChoseGame },
				{ path: "chose", Component: ChoseGame }, { path: "mode", Component: GameMode },
				{ path: "chose_player", Component: ChosePlayer }, { path: "pong", Component: Pong },
				{ path: "breakout", Component: Breakout }, { path: "new_join", Component: NewJoin },
				{ path: "new", Component: NewGame }, { path: "join", Component: JoinGame },
				{ path: "tournaments", Component: Tournaments }, { path: "tournament_table", Component: TournamentTable },
			]},
			{ path: "chat", Component: Chat },
			{ path: "settings", Component: Settings },
			{ path: "friends", Component: Friends },
			{ path: "register", Component: Register },
			{ path: "*", Component: NotFound },
		],
	},
]);

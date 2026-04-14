import { initThemeMode } from "flowbite-react";
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import { RouterProvider } from "react-router";
import { ThemeInit } from "../.flowbite-react/init";
import { router } from "./router";
import "./i18n";
import "./index.css";
import { AuthProvider } from "./context/AuthContext";
import { ChatWsProvider } from "./contexts/ChatWsContext";
import { GameProvider } from "./context/GameContext";
import { LoginModalProvider } from "./context/LoginModalContext";

initThemeMode();

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <AuthProvider>
      <ChatWsProvider>
        <GameProvider>
          <LoginModalProvider>
            <ThemeInit />
            <RouterProvider router={router} />
          </LoginModalProvider>
        </GameProvider>
      </ChatWsProvider>
    </AuthProvider>
  </StrictMode>,
);

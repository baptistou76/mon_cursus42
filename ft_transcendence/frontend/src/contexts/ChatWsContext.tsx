import { createContext, useContext, ReactNode } from "react";
import { useChatWebSocket, ChatMessage } from "../hooks/useChatWebSocket";

type ChatWsContextValue = {
  send: (payload: any) => void;
  lastMessage: ChatMessage | null;
  isConnected: boolean;
};

const ChatWsContext = createContext<ChatWsContextValue>({
  send: () => {},
  lastMessage: null,
  isConnected: false,
});

export const ChatWsProvider = ({ children }: { children: ReactNode }) => {
  const ws = useChatWebSocket();
  return <ChatWsContext.Provider value={ws}>{children}</ChatWsContext.Provider>;
};

export const useChatWs = () => useContext(ChatWsContext);

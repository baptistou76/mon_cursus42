import { useState, useEffect, useRef } from "react";

import { useAuth } from "../context/AuthContext";

export type ChatMessage = {
  type: "CHAT_MESSAGE" | "STATUS_UPDATE" | "GAME_INVITE" | "TOURNAMENT_NOTIF";
  senderId?: number;
  recipientId?: number;
  userId?: number; 
  content?: string;
  isOnline?: boolean;
  timestamp: string;
};

const getWsUrl = (path: string): string => {
  const apiUrl = (import.meta as any).env?.VITE_API_URL || '/api';
  
  // If apiUrl is relative, construct absolute URL from current location
  if (apiUrl.startsWith('/')) {
    const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const host = window.location.host;
    return `${protocol}//${host}${apiUrl}${path}`;
  }
  
  // If absolute URL, convert to WebSocket URL
  const url = new URL(apiUrl);
  url.protocol = url.protocol === "https:" ? "wss:" : "ws:";
  url.pathname = url.pathname.replace(/\/$/, "") + path;
  return url.toString();
};

const WS_URL = getWsUrl("/ws/chat");

export const useChatWebSocket = () => {
  const { isAuthenticated } = useAuth();
  const [isConnected, setIsConnected] = useState(false);
  const [lastMessage, setLastMessage] = useState<ChatMessage | null>(null);

  const g = globalThis as any;
  if (!g.__CHAT_WS__) g.__CHAT_WS__ = null as WebSocket | null;
  if (!g.__CHAT_WS_RECONNECT__)
    g.__CHAT_WS_RECONNECT__ = null as ReturnType<typeof setTimeout> | null;
  if (typeof g.__CHAT_WS_CONNECTING__ !== "boolean")
    g.__CHAT_WS_CONNECTING__ = false as boolean;
  if (typeof g.__CHAT_WS_CONNECTED__ !== "boolean")
    g.__CHAT_WS_CONNECTED__ = false as boolean;
  if (!g.__CHAT_WS_LISTENERS__)
    g.__CHAT_WS_LISTENERS__ = new Set<(data: ChatMessage) => void>();

  useEffect(() => {
    const ensureSocket = () => {
      if (!isAuthenticated) {
        if (g.__CHAT_WS_RECONNECT__) {
          clearTimeout(g.__CHAT_WS_RECONNECT__);
          g.__CHAT_WS_RECONNECT__ = null;
        }
        if (g.__CHAT_WS__ && g.__CHAT_WS__.readyState === WebSocket.OPEN) {
          g.__CHAT_WS__.close(1000, "User logged out");
        }
        g.__CHAT_WS__ = null;
        g.__CHAT_WS_CONNECTING__ = false;
        g.__CHAT_WS_CONNECTED__ = false;
        setIsConnected(false);
        return;
      }

      if (g.__CHAT_WS_CONNECTING__) return;
      if (
        g.__CHAT_WS__ &&
        (g.__CHAT_WS__.readyState === WebSocket.OPEN ||
          g.__CHAT_WS__.readyState === WebSocket.CONNECTING)
      )
        return;

      g.__CHAT_WS_CONNECTING__ = true;
      const socket = new WebSocket(WS_URL);
      g.__CHAT_WS__ = socket;

      socket.onopen = () => {
        console.log("WS: Connected");
        g.__CHAT_WS_CONNECTING__ = false;
        g.__CHAT_WS_CONNECTED__ = true;
        setIsConnected(true);
      };

      socket.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data) as ChatMessage;
          g.__CHAT_WS_LISTENERS__.forEach((fn: (d: ChatMessage) => void) =>
            fn(data),
          );
        } catch (e) {
          console.error("WS: Parse error:", e);
        }
      };

      socket.onclose = (event) => {
        console.log(`WS: Closed (${event.code})`);
        g.__CHAT_WS_CONNECTING__ = false;
        g.__CHAT_WS_CONNECTED__ = false;
        g.__CHAT_WS__ = null;
        setIsConnected(false);
        if (event.code !== 1000 && isAuthenticated) {
          g.__CHAT_WS_RECONNECT__ = setTimeout(ensureSocket, 2000);
        }
      };

      socket.onerror = () => {
        console.error("WS: Error");
        g.__CHAT_WS_CONNECTING__ = false;
      };
    };

    ensureSocket();

    // Subscribe this hook instance to shared messages
    const listener = (data: ChatMessage) => setLastMessage(data);
    g.__CHAT_WS_LISTENERS__.add(listener);

    return () => {
      g.__CHAT_WS_LISTENERS__.delete(listener);
    };
  }, [isAuthenticated]);

  const send = (payload: any) => {
    if (g.__CHAT_WS__ && g.__CHAT_WS__.readyState === WebSocket.OPEN) {
      try {
        g.__CHAT_WS__.send(JSON.stringify(payload));
      } catch (e) {
        console.error("WS: Failed to send message:", payload, e);
      }
    } else {
      console.warn("WS: Cannot send message. Connection is not OPEN.");
    }
  };

  return { send, lastMessage, isConnected };
};

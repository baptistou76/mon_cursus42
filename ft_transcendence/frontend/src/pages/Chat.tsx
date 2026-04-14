import { useChatWs } from "../contexts/ChatWsContext";
import type { ChatMessage } from "../hooks/useChatWebSocket";
import { useAuth } from "../context/AuthContext";
import { useTranslation } from "react-i18next";
import { TextInput, Button, Badge, Spinner } from "flowbite-react";
import { useState, useEffect, useRef } from "react";
import { useLocation, useNavigate } from "react-router";

const API_URL = (import.meta as any).env?.VITE_API_URL || '/api';

type Friend = {
  id: number;
  display_name: string;
  avatar: string;
  is_online: boolean;
};

export default function Chat() {
  const { t } = useTranslation();
  const location = useLocation();
  const navigate = useNavigate();
  const initialRecipientId = location.state?.recipientId as number | undefined;

  const { send, lastMessage, isConnected } = useChatWs();
  const { user, isAuthenticated } = useAuth();
  
  useEffect(() => {
    if (isAuthenticated === false) {
      navigate("/");
    }
  }, [isAuthenticated, navigate]);
  const [input, setInput] = useState("");
  const [messages, setMessages] = useState<ChatMessage[]>([]);
  const messagesEndRef = useRef<HTMLDivElement>(null);

  const [friends, setFriends] = useState<Friend[]>([]);
  const [onlineUsers, setOnlineUsers] = useState<Set<number>>(new Set());
  const [selectedUserId, setSelectedUserId] = useState<number | undefined>(
    initialRecipientId,
  );
  const [loading, setLoading] = useState(false);
  const [showSidebar, setShowSidebar] = useState(true);

  useEffect(() => {
    if (!selectedUserId) return;
    const cacheKey = `chat_messages_${selectedUserId}`;
    try {
      const cached = sessionStorage.getItem(cacheKey);
      if (cached) {
        const parsed = JSON.parse(cached) as ChatMessage[];
        setMessages(parsed);
      }
    } catch (e) {
      console.error("Failed to load cached messages", e);
    }
  }, [selectedUserId]);

  useEffect(() => {
    if (!selectedUserId || messages.length === 0) return;
    const cacheKey = `chat_messages_${selectedUserId}`;
    try {
      sessionStorage.setItem(cacheKey, JSON.stringify(messages));
    } catch (e) {
      console.error("Failed to cache messages", e);
    }
  }, [selectedUserId, messages]);

  useEffect(() => {
    const fetchFriends = async () => {
      if (!isAuthenticated) return;
      setLoading(true);
      try {
        const res = await fetch(`${API_URL}/friends`, { credentials: "include" });
        if (!res.ok) throw new Error("Failed to fetch friends.");
        const data: Friend[] = await res.json();
        setFriends(data);
        setOnlineUsers((prev) => {
          const s = new Set(prev);
          data.forEach((f) => {
            if (f.is_online) s.add(f.id);
          });
          return s;
        });

        setSelectedUserId((prev) => prev ?? data[0]?.id);
      } catch (e) {
        console.error(e);
      } finally {
        setLoading(false);
      }
    };
    fetchFriends();
  }, [isAuthenticated]);

  useEffect(() => {
    if (!lastMessage) return;

    if (lastMessage.type === "STATUS_UPDATE") {
      const uid = (lastMessage as any).userId as number | undefined;
      const online = (lastMessage as any).isOnline as boolean | undefined;
      if (uid && typeof online === "boolean") {
        setOnlineUsers((prev) => {
          const s = new Set(prev);
          online ? s.add(uid) : s.delete(uid);
          return s;
        });
        setFriends((prev) =>
          prev.map((f) => (f.id === uid ? { ...f, is_online: online } : f)),
        );
      }
      return;
    }

    if (lastMessage.type === "CHAT_MESSAGE") {
      if (
        (selectedUserId && lastMessage.senderId === selectedUserId) ||
        (selectedUserId && lastMessage.recipientId === selectedUserId)
      ) {
        setMessages((prev) => {
          const isDuplicate = prev.some(
            (m) =>
              m.timestamp === lastMessage.timestamp &&
              m.senderId === lastMessage.senderId &&
              m.content === lastMessage.content
          );
          if (isDuplicate) return prev;
          return [...prev, lastMessage];
        });
      }
      return;
    }

    if (lastMessage.type === "GAME_INVITE") {
      if (
        (selectedUserId && lastMessage.senderId === selectedUserId) ||
        (selectedUserId && lastMessage.recipientId === selectedUserId)
      ) {
        setMessages((prev) => {
          const isDuplicate = prev.some(
            (m) =>
              m.type === "GAME_INVITE" &&
              m.timestamp === lastMessage.timestamp &&
              m.senderId === lastMessage.senderId
          );
          if (isDuplicate) return prev;
          return [...prev, lastMessage];
        });
      }
      return;
    }

    if ((lastMessage as any).type === "CHAT_BLOCKED") {
      if (
        selectedUserId &&
        ((lastMessage as any).recipientId === selectedUserId ||
          (lastMessage as any).senderId === selectedUserId)
      ) {
        setMessages((prev) => [
          ...prev,
          {
            type: "CHAT_MESSAGE",
            senderId: 0,
            content:
              (lastMessage as any).content ||
              t("chat.blocked"),
            timestamp: (lastMessage as any).timestamp || new Date().toISOString(),
          } as ChatMessage,
        ]);
      }
    }
  }, [lastMessage, selectedUserId]);

  useEffect(() => {
    messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
  }, [messages]);

  const handleSend = (e: React.FormEvent) => {
    e.preventDefault();
    if (input.trim() === "" || !isConnected || !selectedUserId) return;

    send({
      type: "CHAT_MESSAGE",
      recipientId: selectedUserId,
      content: input.trim(),
      timestamp: new Date().toISOString(),
    });
    setInput("");
  };

  if (!isAuthenticated) return null;

  return (
    <div className="mx-auto grid h-[calc(100vh-6rem)] max-w-6xl grid-rows-[auto_1fr_auto] gap-3 p-3 sm:gap-4 sm:p-4 md:grid-cols-[260px_1fr] md:grid-rows-[auto_1fr]">
      <aside className={`rounded-xl border border-gray-200 bg-white p-3 shadow-sm dark:border-gray-700 dark:bg-gray-800 md:row-span-2 ${
        showSidebar ? "block" : "hidden md:block"
      }`}>
        <div className="mb-2 flex items-center justify-between">
          <h3 className="text-sm font-semibold text-gray-700 dark:text-gray-200">
            {t("chat.conversations")}
          </h3>
          <Badge color={isConnected ? "success" : "failure"} size="xs">
            {isConnected ? t("chat.online") : t("chat.offline")}
          </Badge>
        </div>
        {loading ? (
          <div className="flex items-center justify-center py-8">
            <Spinner size="sm" />
          </div>
        ) : friends.length === 0 ? (
          <div className="py-6 text-center text-xs text-gray-500 dark:text-gray-400">
            {t("chat.noFriends")}
          </div>
        ) : (
          <ul className="-mx-2 max-h-[50vh] space-y-1 overflow-y-auto px-1 md:max-h-full">
            {friends.map((f) => {
              const isOnline = onlineUsers.has(f.id) || f.is_online;
              const selected = selectedUserId === f.id;
              return (
                <li key={f.id}>
                  <button
                    onClick={() => {
                      setSelectedUserId(f.id);
                      setShowSidebar(false);
                    }}
                    className={`flex w-full items-center gap-3 rounded-lg px-2 py-2 text-left transition ${
                      selected
                        ? "bg-purple-50 text-purple-700 dark:bg-purple-900/30 dark:text-purple-200"
                        : "hover:bg-gray-100 dark:hover:bg-gray-700"
                    }`}
                  >
                    <span className="relative inline-block">
                      <img
                        src={f.avatar}
                        alt={f.display_name}
                        className="h-9 w-9 rounded-full object-cover sm:h-8 sm:w-8"
                      />
                      {isOnline && (
                        <span className="absolute right-0 bottom-0 block h-2.5 w-2.5 rounded-full bg-green-500 ring-2 ring-white dark:ring-gray-800" />
                      )}
                    </span>
                    <span className="flex min-w-0 flex-col">
                      <a
                        href={`/profile/${f.id}`}
                        onClick={(e) => {
                          e.preventDefault();
                          e.stopPropagation();
                          navigate(`/profile/${f.id}`);
                        }}
                        className="truncate text-sm font-medium text-gray-900 hover:text-purple-600 hover:underline dark:text-white dark:hover:text-purple-400"
                      >
                        {f.display_name}
                      </a>
                      <span className="truncate text-[11px] text-gray-500 dark:text-gray-400">
                        ID: {f.id}
                      </span>
                    </span>
                  </button>
                </li>
              );
            })}
          </ul>
        )}
        <div className="mt-3 text-center">
          <button
            onClick={() => navigate("/friends")}
            className="text-xs text-gray-500 hover:text-gray-700 dark:text-gray-400 dark:hover:text-gray-300"
          >
            {t("chat.manageFriends")}
          </button>
        </div>
      </aside>

      {/* Header */}
      <div className={`flex items-center justify-between md:col-start-2 ${
        showSidebar ? "hidden md:flex" : "flex"
      }`}>
        <div className="flex items-center gap-2 min-w-0 flex-1">
          <button
            onClick={() => setShowSidebar(true)}
            className="md:hidden flex-shrink-0 rounded-lg p-1.5 text-gray-600 hover:bg-gray-100 dark:text-gray-400 dark:hover:bg-gray-700"
          >
            <svg className="h-5 w-5" fill="none" stroke="currentColor" viewBox="0 0 24 24">
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M15 19l-7-7 7-7" />
            </svg>
          </button>
          <h2 className="text-base font-bold text-gray-900 dark:text-white sm:text-xl truncate">
            {selectedUserId
              ? `${friends.find((f) => f.id === selectedUserId)?.display_name || t("chat.gameInvite.user") + " " + selectedUserId}`
              : t("chat.selectConversation")}
          </h2>
        </div>
        <div className="flex items-center gap-1.5 sm:gap-2 flex-shrink-0">
          <Button
            color="purple"
            size="xs"
            disabled={!isConnected || !selectedUserId}
            onClick={() => {
              if (!selectedUserId) return;
              send({
                type: "GAME_INVITE",
                recipientId: selectedUserId,
                content: "Let's play Pong!",
                timestamp: new Date().toISOString(),
              });
            }}
            className="text-xs sm:text-sm"
          >
            <span className="hidden sm:inline">{t("chat.inviteToPlay")}</span>
            <span className="sm:hidden">🎮</span>
          </Button>
          <Button
            color="gray"
            size="xs"
            disabled={!selectedUserId || messages.length === 0}
            onClick={() => {
              if (!selectedUserId) return;
              const cacheKey = `chat_messages_${selectedUserId}`;
              sessionStorage.removeItem(cacheKey);
              setMessages([]);
            }}
            className="text-xs sm:text-sm"
          >
            <span className="hidden sm:inline">{t("chat.clearChat")}</span>
            <span className="sm:hidden">🗑️</span>
          </Button>
        </div>
      </div>

      {/* Chat Area */}
      <div className={`flex min-h-0 flex-col md:col-start-2 ${
        showSidebar ? "hidden md:flex" : "flex"
      }`}>
        <div className="flex-1 space-y-3 overflow-y-auto rounded-xl border border-gray-200 bg-gray-50 p-3 shadow-sm dark:border-gray-700 dark:bg-gray-800 sm:space-y-4 sm:p-4">
          {(!selectedUserId || messages.length === 0) && (
            <div className="flex h-full items-center justify-center text-gray-400">
              {!selectedUserId ? t("chat.pickUser") : t("chat.noMessages")}
            </div>
          )}

          {messages.map((msg, index) => {
            const isMe = user?.id === msg.senderId;
            if (msg.type === "GAME_INVITE") {
              const recipientName = friends.find((f) => f.id === msg.recipientId)?.display_name || `${t("chat.gameInvite.user")} ${msg.recipientId}`;
              const senderName = friends.find((f) => f.id === msg.senderId)?.display_name || `${t("chat.gameInvite.user")} ${msg.senderId}`;
              const inviteText = isMe 
                ? t("chat.gameInvite.youInvited", { name: recipientName })
                : t("chat.gameInvite.invitedYou", { name: senderName });
              return (
                <div key={index} className="flex justify-center">
                  <div className="w-full max-w-md rounded-xl border border-purple-300 bg-purple-50 p-4 text-purple-800 shadow-sm dark:border-purple-700 dark:bg-purple-900/20 dark:text-purple-200">
                    <div className="mb-2 flex items-center justify-between">
                      <div className="text-sm font-semibold">{t("chat.gameInvite.title")}</div>
                      <div className="text-xs opacity-70">
                        {new Date(msg.timestamp).toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" })}
                      </div>
                    </div>
                    <div className="mb-3 text-sm">
                      {inviteText}
                    </div>
                    <div className="flex justify-end gap-2">
                      <Button
                        size="xs"
                        color="purple"
                        onClick={() => {
                          setMessages((prev) => {
                            const filtered = prev.filter((_, i) => i !== index);
                            if (selectedUserId) {
                              const cacheKey = `chat_messages_${selectedUserId}`;
                              sessionStorage.setItem(cacheKey, JSON.stringify(filtered));
                            }
                            return filtered;
                          });
                          setTimeout(() => navigate("/game"), 0);
                        }}
                      >
                        {t("chat.gameInvite.accept")}
                      </Button>
                    </div>
                  </div>
                </div>
              );
            }
            return (
              <div
                key={index}
                className={`flex ${isMe ? "justify-end" : "justify-start"}`}
              >
                <div
                  className={`max-w-[85%] rounded-2xl px-3 py-2 shadow-sm sm:max-w-[75%] sm:px-4 md:max-w-[60%] ${
                    isMe
                      ? "rounded-br-none bg-blue-600 text-white"
                      : "rounded-bl-none border border-gray-100 bg-white text-gray-900 dark:border-gray-600 dark:bg-gray-700 dark:text-white"
                  }`}
                >
                  {!isMe && (
                    <div className="mb-1 text-xs font-semibold text-gray-500 dark:text-gray-400">
                      <a
                        href={`/profile/${msg.senderId}`}
                        onClick={(e) => {
                          e.preventDefault();
                          navigate(`/profile/${msg.senderId}`);
                        }}
                        className="hover:text-purple-600 hover:underline dark:hover:text-purple-400"
                      >
                        {friends.find((f) => f.id === msg.senderId)?.display_name ?? `User ${msg.senderId}`}
                      </a>
                    </div>
                  )}
                  {isMe && (
                    <div className="mb-1 text-xs font-semibold text-gray-500 dark:text-gray-400 text-right">
                      {t("chat.you")}
                    </div>
                  )}
                  <div className="break-words text-sm leading-relaxed">
                    {msg.content}
                  </div>
                  <div
                    className={`mt-1 text-right text-[10px] ${isMe ? "text-blue-200" : "text-gray-400"}`}
                  >
                    {new Date(msg.timestamp).toLocaleTimeString([], {
                      hour: "2-digit",
                      minute: "2-digit",
                    })}
                  </div>
                </div>
              </div>
            );
          })}
          <div ref={messagesEndRef} />
        </div>

        {/* Input Area */}
        <form onSubmit={handleSend} className="mt-3 flex gap-2 sm:mt-4">
          <TextInput
            type="text"
            value={input}
            onChange={(e) => setInput(e.target.value)}
            placeholder={selectedUserId ? t("chat.placeholder") : t("chat.placeholderDisabled")}
            disabled={!isConnected || !selectedUserId}
            className="flex-grow text-sm sm:text-base"
            shadow
          />
          <Button
            type="submit"
            disabled={!isConnected || !input.trim() || !selectedUserId}
            color="purple"
            size="sm"
            className="whitespace-nowrap px-4 sm:px-6"
          >
            <span className="hidden sm:inline">{t("chat.send")}</span>
            <span className="sm:hidden">📤</span>
          </Button>
        </form>
      </div>
    </div>
  );
}

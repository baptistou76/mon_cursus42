import { useTranslation } from "react-i18next";
import { useState, useEffect } from "react";
import { useAuth } from "../context/AuthContext";
import { Button, TextInput, Spinner, Card } from "flowbite-react";
import { HiUserAdd, HiCheck, HiExclamation, HiChat, HiOutlineExclamationCircle } from "react-icons/hi";
import { useChatWs } from "../contexts/ChatWsContext";
import { useNavigate } from "react-router";

const API_URL = (import.meta as any).env?.VITE_API_URL || '/api';

type Friend = {
  id: number;
  display_name: string;
  avatar: string;
  is_online: boolean;
};
type BlockedUser = {
  id: number;
  display_name?: string;
  avatar: string;
};

type SearchResult = {
  id: number;
  display_name: string;
  avatar: string;
  is_online: boolean;
};

type ToastMessage = {
  content: string;
  type: "success" | "error";
};

export default function Friends() {
  const { t } = useTranslation();
  const { user, isAuthenticated } = useAuth();
  const navigate = useNavigate();
  
  useEffect(() => {
    if (isAuthenticated === false) {
      navigate("/");
    }
  }, [isAuthenticated, navigate]);
  const [friends, setFriends] = useState<Friend[]>([]);
  const [onlineUsers, setOnlineUsers] = useState<Set<number>>(new Set());
  const [searchName, setSearchName] = useState("");
  const [searchResults, setSearchResults] = useState<SearchResult[]>([]);
  const [searching, setSearching] = useState(false);
  const [loading, setLoading] = useState(false);
  const [message, setMessage] = useState<ToastMessage | null>(null);
  const [blocked, setBlocked] = useState<BlockedUser[]>([]);
  const [showDeleteModal, setShowDeleteModal] = useState(false);
  const [friendToDelete, setFriendToDelete] = useState<{ id: number; name: string } | null>(null);

  const { lastMessage } = useChatWs();

  const fetchFriends = async () => {
    if (!isAuthenticated) return;
    setLoading(true);
    try {
      const res = await fetch(`${API_URL}/friends`, {
        credentials: "include",
      });
      if (!res.ok) throw new Error("Failed to fetch friends.");
      const data: Friend[] = await res.json();

      console.log(
        "[Friends] Loaded friends:",
        data.map((f) => ({
          id: f.id,
          name: f.display_name,
          online: f.is_online,
        })),
      );
      setFriends(data);

      setOnlineUsers((prev) => {
        const newSet = new Set(prev);
        data.forEach((friend) => {
          if (friend.is_online) {
            newSet.add(friend.id);
          }
        });
        console.log(
          "[Friends] Initial online users from friends list:",
          Array.from(newSet),
        );
        return newSet;
      });
    } catch (error: any) {
      console.error("Error fetching friends:", error);
      setMessage({
        content: error.message || t("toast.Error") + " " + t("friends.error.fetchFriends"),
        type: "error",
      });
    } finally {
      setLoading(false);
    }
  };

  const fetchBlocked = async () => {
    if (!isAuthenticated) return;
    try {
      const res = await fetch(`${API_URL}/me/blocked`, { credentials: "include" });
      if (!res.ok) throw new Error(t("friends.error.fetchBlocked"));
      const data: BlockedUser[] = await res.json();
      setBlocked(data);
    } catch (error: any) {
      console.error("Error fetching blocked:", error);
    }
  };

  useEffect(() => {
    fetchFriends();
    fetchBlocked();

    const intervalId = setInterval(() => {
      if (isAuthenticated) {
        fetchFriends();
      }
    }, 10000);

    return () => clearInterval(intervalId);
  }, [isAuthenticated]);

  useEffect(() => {
    if (lastMessage && lastMessage.type === "STATUS_UPDATE") {
      const userId = (lastMessage as any).userId;
      const isOnline = (lastMessage as any).isOnline;

      console.log(
        `[Friends] Status update received: User ${userId} is now ${isOnline ? "online" : "offline"}`,
      );
      console.log(
        `[Friends] Current friends:`,
        friends.map((f) => ({
          id: f.id,
          name: f.display_name,
          online: f.is_online,
        })),
      );

      setOnlineUsers((prev) => {
        const newSet = new Set(prev);
        if (isOnline) {
          newSet.add(userId);
        } else {
          newSet.delete(userId);
        }
        console.log(`[Friends] Updated onlineUsers set:`, Array.from(newSet));
        return newSet;
      });

      setFriends((prev) => {
        const updated = prev.map((friend) =>
          friend.id === userId ? { ...friend, is_online: isOnline } : friend,
        );
        console.log(
          `[Friends] Updated friends list:`,
          updated.map((f) => ({
            id: f.id,
            name: f.display_name,
            online: f.is_online,
          })),
        );
        return updated;
      });

      setSearchResults((prev) =>
        prev.map((result) =>
          result.id === userId ? { ...result, is_online: isOnline } : result,
        ),
      );

      console.log(
        `Status update: User ${userId} is now ${isOnline ? "online" : "offline"}`,
      );
    }
  }, [lastMessage]);

  const handleSearch = async (e: React.FormEvent) => {
    e.preventDefault();
    setMessage(null);
    if (!searchName.trim() || !user) return;

    if (searchName.trim().length < 2) {
      setMessage({
        content: t("friends.error.searchMinLength"),
        type: "error",
      });
      return;
    }

    setSearching(true);
    try {
      const res = await fetch(
        `${API_URL}/users?search=${encodeURIComponent(searchName.trim())}`,
        {
          credentials: "include",
        },
      );

      if (!res.ok) {
        const result = await res.json();
        throw new Error(result.error || t("friends.error.searchUsers"));
      }

      const results: SearchResult[] = await res.json();
      setSearchResults(results);

      if (results.length === 0) {
        setMessage({ content: t("friends.error.noResults"), type: "error" });
      }
    } catch (error: any) {
      setMessage({
        content: error.message || t("toast.Error") + " " + t("friends.error.searchUsers"),
        type: "error",
      });
      setSearchResults([]);
    } finally {
      setSearching(false);
    }
  };

  const handleAddFriendById = async (friendId: number, displayName: string) => {
    setMessage(null);

    try {
      const res = await fetch(`${API_URL}/friends/${friendId}`, {
        method: "POST",
        credentials: "include",
      });

      const result = await res.json();

      if (!res.ok) {
        throw new Error(result.error || t("friends.error.addFriend"));
      }

      setMessage({
        content: `${displayName} ${t("friends.addSuccess")}`,
        type: "success",
      });
      setSearchName("");
      setSearchResults([]);
      fetchFriends(); 
    } catch (error: any) {
      setMessage({
        content: error.message || t("toast.Error") + " " + t("friends.error.addFriend"),
        type: "error",
      });
    }
  };

  const handleRemoveFriend = async (friendId: number) => {
    setMessage(null);
    try {
      const res = await fetch(`${API_URL}/friends/${friendId}`, {
        method: "DELETE",
        credentials: "include",
      });

      if (!res.ok) {
        const errorData = await res.json().catch(() => ({}));
        throw new Error(errorData.error || t("friends.error.removeFriend"));
      }

      setMessage({ content: t("friends.removeSuccess"), type: "success" });
      setShowDeleteModal(false);
      setFriendToDelete(null);
      fetchFriends();
    } catch (error: any) {
      setMessage({
        content:
          error.message || t("toast.Error") + " " + t("friends.error.removeFriend"),
        type: "error",
      });
    }
  };

  const confirmRemoveFriend = (friendId: number, friendName: string) => {
    setFriendToDelete({ id: friendId, name: friendName });
    setShowDeleteModal(true);
  };

  const handleBlock = async (userId: number, displayName?: string) => {
    setMessage(null);
    try {
      const res = await fetch(`${API_URL}/block/${userId}`, {
        method: "POST",
        credentials: "include",
      });
      if (!res.ok) {
        const e = await res.json().catch(() => ({}));
        throw new Error(e.error || t("friends.error.blockUser"));
      }
      setMessage({ content: `${displayName || userId} ${t("friends.blockSuccess")}`, type: "success" });
      await Promise.all([fetchBlocked(), fetchFriends()]);
    } catch (error: any) {
      setMessage({ content: error.message || t("friends.error.blockUser"), type: "error" });
    }
  };

  const handleUnblock = async (userId: number) => {
    setMessage(null);
    try {
      const res = await fetch(`${API_URL}/block/${userId}`, {
        method: "DELETE",
        credentials: "include",
      });
      if (!res.ok) {
        const e = await res.json().catch(() => ({}));
        throw new Error(e.error || t("friends.error.unblockUser"));
      }
      setMessage({ content: `${t("friends.unblockSuccess")} ${userId}.`, type: "success" });
      await Promise.all([fetchBlocked(), fetchFriends()]);
    } catch (error: any) {
      setMessage({ content: error.message || t("friends.error.unblockUser"), type: "error" });
    }
  };

  const handleOpenChat = (friendId: number) => {
    navigate("/chat", { state: { recipientId: friendId } });
  };

  if (loading)
    return (
      <div className="flex min-h-screen items-center justify-center">
        <Spinner color="purple" size="xl" />
      </div>
    );
  if (!isAuthenticated) return null;

  return (
    <div className="mx-auto max-w-4xl space-y-4 p-3 sm:space-y-6 sm:p-4">
      <h2 className="pb-3 text-2xl font-bold sm:pb-4 sm:text-3xl">{t("friends.title")}</h2>

      {/* Toast Notifications */}
      {message && (
        <div className="mb-3 flex w-full max-w-md items-center rounded-lg bg-white p-3 text-sm text-gray-500 shadow dark:bg-gray-800 dark:text-gray-400 sm:mb-4 sm:p-4 sm:text-base">
          <div
            className={`inline-flex h-8 w-8 shrink-0 items-center justify-center rounded-lg ${
              message.type === "success"
                ? "bg-green-100 text-green-500 dark:bg-green-800 dark:text-green-200"
                : "bg-red-100 text-red-500 dark:bg-red-700 dark:text-red-200"
            }`}
          >
            {message.type === "success" ? (
              <HiCheck className="h-5 w-5" />
            ) : (
              <HiExclamation className="h-5 w-5" />
            )}
          </div>
          <div className="ml-3 text-sm font-normal">{message.content}</div>
        </div>
      )}

      {/* Search Users Form */}
      <div className="mb-6 w-full max-w-2xl sm:mb-8">
        <form
          onSubmit={handleSearch}
          className="flex flex-col gap-2 rounded-lg bg-gray-50 p-3 shadow-md dark:bg-gray-800 sm:flex-row sm:p-4"
        >
          <TextInput
            type="text"
            value={searchName}
            onChange={(e) => setSearchName(e.target.value)}
            placeholder={t("friends.searchPlaceholder")}
            required
            className="flex-grow"
            minLength={2}
          />
          <Button type="submit" color="purple" disabled={searching} className="w-full sm:w-auto">
            {searching ? (
              <Spinner size="sm" className="mr-2" />
            ) : (
              <HiUserAdd className="mr-2 h-4 w-4 sm:h-5 sm:w-5" />
            )}
            {t("friends.searchButton")}
          </Button>
        </form>

        {/* Search Results */}
        {searchResults.length > 0 && (
          <div className="mt-3 rounded-lg bg-white p-3 shadow-md dark:bg-gray-700 sm:mt-4 sm:p-4">
            <h3 className="mb-2 text-base font-semibold sm:mb-3 sm:text-lg">
              {t("friends.searchResults")} ({searchResults.length})
            </h3>
            <ul className="divide-y divide-gray-200 dark:divide-gray-600">
              {searchResults.map((result) => {
                const isOnline = onlineUsers.has(result.id) || result.is_online;
                return (
                  <li
                    key={result.id}
                    className="flex flex-col gap-2 py-2 sm:flex-row sm:items-center sm:justify-between sm:py-3"
                  >
                    <div className="flex items-center space-x-2 sm:space-x-3">
                      <div className="relative">
                        <img
                          src={result.avatar}
                          alt={result.display_name}
                          className="h-9 w-9 rounded-full object-cover sm:h-10 sm:w-10"
                        />
                        {isOnline && (
                          <span className="absolute right-0 bottom-0 block h-2.5 w-2.5 rounded-full bg-green-500 ring-2 ring-white dark:ring-gray-700 sm:h-3 sm:w-3"></span>
                        )}
                      </div>
                      <div className="min-w-0 flex-1">
                        <a
                          href={`/profile/${result.id}`}
                          onClick={(e) => {
                            e.preventDefault();
                            navigate(`/profile/${result.id}`);
                          }}
                          className="truncate text-sm font-medium text-gray-900 hover:text-purple-600 hover:underline dark:text-white dark:hover:text-purple-400 sm:text-base"
                        >
                          {result.display_name}
                        </a>
                        <span
                          className={`ml-1 text-xs sm:ml-2 ${isOnline ? "text-green-500" : "text-gray-500 dark:text-gray-400"}`}
                        >
                          {isOnline ? t("friends.online") : t("friends.offline")}
                        </span>
                      </div>
                    </div>
                    <Button
                      size="xs"
                      color="purple"
                      onClick={() =>
                        handleAddFriendById(result.id, result.display_name)
                      }
                      className="w-full sm:w-auto"
                    >
                      <HiUserAdd className="mr-1 h-3.5 w-3.5 sm:h-4 sm:w-4" />
                      <span className="text-xs sm:text-sm">{t("friends.add")}</span>
                    </Button>
                  </li>
                );
              })}
            </ul>
          </div>
        )}
      </div>

      {/* Friends List */}
      <div className="w-full max-w-2xl">
        <h3 className="mb-2 text-lg font-semibold sm:mb-3 sm:text-xl">
          {t("friends.yourFriends")} ({friends.length})
        </h3>

        {friends.length === 0 ? (
          <p className="text-gray-500 dark:text-gray-400">
            {t("friends.noFriends")}
          </p>
        ) : (
          <ul className="w-full divide-y divide-gray-200 dark:divide-gray-700">
            {friends.map((friend) => {
              const isOnline = onlineUsers.has(friend.id) || friend.is_online;
              const isBlocked = blocked.some((b) => b.id === friend.id);
              return (
                <li
                  key={friend.id}
                  className="flex flex-col gap-2 py-2 sm:flex-row sm:items-center sm:justify-between sm:py-3 sm:py-4"
                >
                  <div className="flex items-center space-x-2 sm:space-x-3">
                    <div className="relative">
                      <img
                        src={friend.avatar}
                        alt={friend.display_name}
                        className="h-9 w-9 rounded-full object-cover sm:h-10 sm:w-10"
                      />
                      {isOnline && (
                        <span className="absolute right-0 bottom-0 block h-2.5 w-2.5 rounded-full bg-green-500 ring-2 ring-white dark:ring-gray-800 sm:h-3 sm:w-3"></span>
                      )}
                    </div>
                    <div className="min-w-0 flex-1">
                      <a
                        href={`/profile/${friend.id}`}
                        onClick={(e) => {
                          e.preventDefault();
                          navigate(`/profile/${friend.id}`);
                        }}
                        className="truncate text-sm font-medium text-gray-900 hover:text-purple-600 hover:underline dark:text-white dark:hover:text-purple-400 sm:text-base"
                      >
                        {friend.display_name}
                      </a>
                      <span className="ml-1 text-xs text-gray-500 dark:text-gray-400 sm:ml-2">
                        (ID: {friend.id})
                      </span>
                      <br />
                      <span
                        className={`text-xs ${isOnline ? "text-green-500" : "text-gray-500 dark:text-gray-400"}`}
                      >
                        {isOnline ? t("friends.online") : t("friends.offline")}
                      </span>
                    </div>
                  </div>

                  <div className="flex flex-wrap gap-1.5 sm:gap-2">
                    {isOnline && !isBlocked && (
                      <Button
                        size="xs"
                        color="purple"
                        onClick={() => handleOpenChat(friend.id)}
                        className="flex-1 sm:flex-none"
                      >
                        <HiChat className="mr-1 h-3.5 w-3.5 sm:h-4 sm:w-4" />
                        <span className="text-xs sm:text-sm">{t("friends.chat")}</span>
                      </Button>
                    )}
                    {!isBlocked ? (
                      <Button
                        size="xs"
                        color="warning"
                        onClick={() => handleBlock(friend.id, friend.display_name)}
                        className="flex-1 sm:flex-none"
                      >
                        <span className="text-xs sm:text-sm">{t("friends.block")}</span>
                      </Button>
                    ) : (
                      <Button
                        size="xs"
                        color="gray"
                        onClick={() => handleUnblock(friend.id)}
                        className="flex-1 sm:flex-none"
                      >
                        <span className="text-xs sm:text-sm">{t("friends.unblock")}</span>
                      </Button>
                    )}
                    <Button
                      size="xs"
                      color="failure"
                      onClick={() => confirmRemoveFriend(friend.id, friend.display_name)}
                      className="flex-1 sm:flex-none"
                    >
                      <span className="text-xs sm:text-sm">{t("friends.remove")}</span>
                    </Button>
                  </div>
                </li>
              );
            })}
          </ul>
        )}
      </div>

      {/* Blocked Users */}
      <div className="w-full max-w-2xl">
        <h3 className="mb-2 text-lg font-semibold sm:text-xl">{t("friends.blockedUsers")} ({blocked.length})</h3>
        {blocked.length === 0 ? (
          <p className="text-sm text-gray-500 dark:text-gray-400 sm:text-base">{t("friends.noBlockedUsers")}</p>
        ) : (
          <ul className="divide-y divide-gray-200 dark:divide-gray-700">
            {blocked.map((b) => (
              <li key={b.id} className="flex flex-col gap-2 py-2 sm:flex-row sm:items-center sm:justify-between sm:py-3">
                <div className="flex items-center gap-2 sm:gap-3">
                  <img
                    src={b.avatar}
                    alt={b.display_name || String(b.id)}
                    className="h-7 w-7 rounded-full object-cover sm:h-8 sm:w-8"
                  />
                  <div className="min-w-0 flex-1 text-sm">
                    <a
                      href={`/profile/${b.id}`}
                      onClick={(e) => {
                        e.preventDefault();
                        navigate(`/profile/${b.id}`);
                      }}
                      className="truncate font-medium text-gray-900 hover:text-purple-600 hover:underline dark:text-white dark:hover:text-purple-400"
                    >
                      {b.display_name || `User ${b.id}`}
                    </a>
                    <div className="text-xs text-gray-500 dark:text-gray-400">ID: {b.id}</div>
                  </div>
                </div>
                <Button size="xs" color="gray" onClick={() => handleUnblock(b.id)} className="w-full sm:w-auto">
                  <span className="text-xs sm:text-sm">{t("friends.unblock")}</span>
                </Button>
              </li>
            ))}
          </ul>
        )}
      </div>

      {/* Delete Confirmation Modal */}
      {showDeleteModal && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-gray-900/50 dark:bg-gray-900/80">
          <Card className="w-full max-w-md">
            <div className="text-center">
              <HiOutlineExclamationCircle className="mx-auto mb-4 h-14 w-14 text-gray-400 dark:text-gray-200" />
              <h3 className="mb-5 text-lg font-normal text-gray-500 dark:text-gray-400">
                {t("friends.removeConfirm")} <span className="font-semibold">{friendToDelete?.name}</span>?
              </h3>
              <div className="flex justify-center gap-4">
                <Button
                  color="failure"
                  onClick={() => friendToDelete && handleRemoveFriend(friendToDelete.id)}
                >
                  {t("friends.confirmYes")}
                </Button>
                <Button color="gray" onClick={() => setShowDeleteModal(false)}>
                  {t("friends.confirmNo")}
                </Button>
              </div>
            </div>
          </Card>
        </div>
      )}
    </div>
  );
}

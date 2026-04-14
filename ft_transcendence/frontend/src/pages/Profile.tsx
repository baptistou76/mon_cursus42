import { useEffect, useState } from "react";
import { useNavigate } from "react-router";
import { Card, Spinner, Badge, Avatar, Pagination } from "flowbite-react";
import { useTranslation } from "react-i18next";
import { useAuth } from "../context/AuthContext";
import { useParams } from "react-router";

type Stats = { wins: number; losses: number };
type MatchItem = {
  id: number;
  played_at: string;
  player1_id: number;
  player2_id: number;
  winner_id: number | null;
  result: "win" | "loss" | "draw";
  opponent: { id: number; display_name: string | null; avatar: string };
  details?: any;
};

type HistoryResponse = {
  matches: MatchItem[];
  total: number;
  page: number;
  limit: number;
  totalPages: number;
};

const API_URL = (import.meta as any).env?.VITE_API_URL || '/api';

type UserProfile = {
  id: number;
  display_name: string;
  avatar: string;
  email?: string;
};

export default function Profile() {
  const { t } = useTranslation();
  const { isAuthenticated, user } = useAuth();
  const navigate = useNavigate();
  const { userId } = useParams<{ userId?: string }>();
  const [loading, setLoading] = useState(true);
  const [stats, setStats] = useState<Stats | null>(null);
  const [history, setHistory] = useState<MatchItem[]>([]);
  const [profileUser, setProfileUser] = useState<UserProfile | null>(null);
  const [error, setError] = useState<string | null>(null);
  const [currentPage, setCurrentPage] = useState(1);
  const [totalPages, setTotalPages] = useState(1);
  const [totalMatches, setTotalMatches] = useState(0);
  const MATCHES_PER_PAGE = 10;

  const isOwnProfile = !userId || (user && userId === String(user.id));

  useEffect(() => {
    if (isAuthenticated === false) {
      // If explicitly unauthenticated, redirect to home instead of showing message
      navigate("/");
      return;
    }
    if (!isAuthenticated) {
      setLoading(false);
      return;
    }
    setLoading(true);
    setError(null);

    const targetUserId = userId ? Number(userId) : user?.id;

    const fetchProfile = !isOwnProfile && targetUserId
      ? fetch(`${API_URL}/users/${targetUserId}`, { credentials: "include" })
          .then((r) => (r.ok ? r.json() : Promise.reject(new Error(`HTTP ${r.status}`))))
          .then((data: UserProfile) => setProfileUser(data))
      : Promise.resolve();

    const statsEndpoint = isOwnProfile
      ? `${API_URL}/me/stats`
      : `${API_URL}/users/${targetUserId}/stats`;
    const fetchStats = fetch(statsEndpoint, { credentials: "include" })
      .then((r) => (r.ok ? r.json() : Promise.reject(new Error(`HTTP ${r.status}`))))
      .then((data: Stats) => setStats(data));

    const historyEndpoint = isOwnProfile
      ? `${API_URL}/me/history?page=${currentPage}&limit=${MATCHES_PER_PAGE}`
      : `${API_URL}/users/${targetUserId}/history?page=${currentPage}&limit=${MATCHES_PER_PAGE}`;
    const fetchHistory = fetch(historyEndpoint, { credentials: "include" })
      .then((r) => (r.ok ? r.json() : Promise.reject(new Error(`HTTP ${r.status}`))))
      .then((data: HistoryResponse) => {
        setHistory(data.matches);
        setTotalPages(data.totalPages);
        setTotalMatches(data.total);
      });

    Promise.allSettled([fetchProfile, fetchStats, fetchHistory])
      .then((results) => {
        const rejected = results.find((r) => r.status === "rejected");
        if (rejected) setError(t("profile.error.loadFailed"));
      })
      .finally(() => setLoading(false));
  }, [isAuthenticated, userId, user, isOwnProfile, t, currentPage]);

  if (!isAuthenticated) {
    return (
      <div className="mx-auto max-w-3xl rounded-lg bg-white p-6 text-gray-600 shadow-md">
        {t("profile.pleaseLogin")}
      </div>
    );
  }

  const displayUser = isOwnProfile ? user : profileUser;

  return (
    <div className="mx-auto max-w-4xl space-y-6 px-4 sm:px-6 lg:px-8 py-4 sm:py-6">
      {/* Profile Header */}
      <div className="flex items-center gap-4">
        <Avatar
          img={displayUser?.avatar || "/public/avatar.png"}
          rounded
          size="lg"
        />
        <div>
          <h2 className="text-2xl font-bold">
            {displayUser?.display_name || t("profile.title")}
          </h2>
          {isOwnProfile && <p className="text-sm text-gray-500">{t("profile.yourProfile")}</p>}
        </div>
      </div>

      {loading ? (
        <div className="flex items-center justify-center rounded-lg bg-white p-6 shadow">
          <Spinner size="lg" />
        </div>
      ) : (
        <>
          {error && (
            <div className="rounded-lg bg-red-50 p-3 text-sm text-red-700 shadow">
              {error}
            </div>
          )}

          {/* Stats */}
          <div className="grid grid-cols-1 gap-4 sm:grid-cols-2">
            <Card>
              <div className="flex items-center justify-between">
                <span className="text-sm text-gray-500">{t("profile.stats.wins")}</span>
                <Badge color="success">{t("profile.stats.allTime")}</Badge>
              </div>
              <div className="mt-2 text-3xl font-semibold text-green-600">
                {stats?.wins ?? 0}
              </div>
            </Card>
            <Card>
              <div className="flex items-center justify-between">
                <span className="text-sm text-gray-500">{t("profile.stats.losses")}</span>
                <Badge color="failure">{t("profile.stats.allTime")}</Badge>
              </div>
              <div className="mt-2 text-3xl font-semibold text-red-600">
                {stats?.losses ?? 0}
              </div>
            </Card>
          </div>

          {/* Match History */}
          <Card>
            <div className="mb-3 flex items-center justify-between">
              <h3 className="text-lg font-semibold">{t("profile.matchHistory.title")}</h3>
              {totalMatches > 0 && (
                <span className="text-sm text-gray-500">
                  {totalMatches} {totalMatches === 1 ? t("profile.matchHistory.match") : t("profile.matchHistory.matches")}
                </span>
              )}
            </div>
            {history.length === 0 ? (
              <p className="text-sm text-gray-500">{t("profile.matchHistory.noMatches")}</p>
            ) : (
              <div className="overflow-x-auto">
                <table className="min-w-full divide-y divide-gray-200">
                  <thead className="bg-transparent">
                    <tr>
                      <th className="px-6 py-3 text-left text-xs font-medium uppercase tracking-wider text-gray-600 dark:text-gray-300">{t("profile.matchHistory.table.date")}</th>
                      <th className="px-6 py-3 text-left text-xs font-medium uppercase tracking-wider text-gray-600 dark:text-gray-300">{t("profile.matchHistory.table.opponent")}</th>
                      <th className="px-6 py-3 text-left text-xs font-medium uppercase tracking-wider text-gray-600 dark:text-gray-300">{t("profile.matchHistory.table.result")}</th>
                    </tr>
                  </thead>
                  <tbody className="divide-y divide-gray-200 dark:divide-gray-700 bg-transparent">
                    {history.map((m) => {
                      const date = new Date(m.played_at);
                      const formattedDate = date.toLocaleString('fr-FR', {
                        year: 'numeric',
                        month: '2-digit',
                        day: '2-digit',
                        hour: '2-digit',
                        minute: '2-digit',
                        hour12: false,
                        timeZone: Intl.DateTimeFormat().resolvedOptions().timeZone
                      });
                      const resultColor =
                        m.result === "win"
                          ? "success"
                          : m.result === "loss"
                          ? "failure"
                          : "gray";
                      return (
                        <tr key={m.id}>
                          <td className="whitespace-nowrap px-6 py-4 text-sm font-medium text-gray-900 dark:text-white">
                            {formattedDate}
                          </td>
                          <td className="whitespace-nowrap px-6 py-4 text-sm text-gray-500 dark:text-gray-300">
                            <div className="flex items-center gap-2">
                              <img
                                src={m.opponent.avatar}
                                alt={m.opponent.display_name ?? `#${m.opponent.id}`}
                                className="h-6 w-6 rounded-full object-cover"
                              />
                              <span className="text-sm text-gray-900 dark:text-white">
                                {m.opponent.display_name ?? `User #${m.opponent.id}`}
                              </span>
                            </div>
                          </td>
                          <td className="whitespace-nowrap px-6 py-4 text-sm text-gray-500">
                            <Badge color={resultColor as any}>
                              {t(`profile.matchHistory.result.${m.result}`)}
                            </Badge>
                          </td>
                          {/* Score column removed as requested */}
                        </tr>
                      );
                    })}
                  </tbody>
                </table>
              </div>
            )}
            
            {/* Pagination */}
            {totalPages > 1 && (
              <div className="mt-4 flex justify-center">
                <Pagination
                  currentPage={currentPage}
                  totalPages={totalPages}
                  onPageChange={(page) => setCurrentPage(page)}
                  showIcons
                />
              </div>
            )}
          </Card>
        </>
      )}
    </div>
  );
}

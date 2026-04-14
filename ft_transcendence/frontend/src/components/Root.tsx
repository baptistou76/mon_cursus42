import { useRef, useState, useEffect } from "react";
import {
  Button,
  Spinner,
  Navbar,
  NavbarBrand,
  NavbarCollapse,
  NavbarLink,
  NavbarToggle,
  DarkThemeToggle,
  Label,
  Modal,
  ModalBody,
  ModalHeader,
  TextInput,
  Dropdown,
  DropdownHeader,
  DropdownItem,
  DropdownDivider,
  Toast,
} from "flowbite-react";
import { Outlet, Link, useLocation } from "react-router";
import { useAuth } from "../context/AuthContext";
import { useTranslation } from "react-i18next";
import LanguageSwitcher from "./LanguageSwitcher";
import { useChatWs } from "../contexts/ChatWsContext";
import type { ChatMessage } from "../hooks/useChatWebSocket";
import { useNavigate } from "react-router";
import { HiExclamation, HiX } from "react-icons/hi";

export default function Root() {
  const { t } = useTranslation();
  const location = useLocation();
  const isActive = (path: string) => location.pathname === path;
  const {
    user,
    isAuthenticated,
    loading,
    login,
    logout,
    refreshAuth,
    localLogin,
  } = useAuth();
  const { lastMessage, isConnected } = useChatWs();
  const [openModal, setOpenModal] = useState(false);
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");
  const [isSubmitting, setIsSubmitting] = useState(false);
  const navigate = useNavigate();
  
  // Tournament notifications state
  const [tournamentNotifications, setTournamentNotifications] = useState<
    Array<{ id: number; content: string; timestamp: number }>
  >([]);

  const handleLocalLogin = async (e: React.FormEvent) => {
    e.preventDefault();
    setError("");
    setIsSubmitting(true);

    try {
      await localLogin(email, password);
      setOpenModal(false);
      setEmail("");
      setPassword("");
    } catch (err: any) {
      setError(err.message);
    } finally {
      setIsSubmitting(false);
    }
  };

  useEffect(() => {
    if (!lastMessage) return;

    switch (lastMessage.type) {
      case "TOURNAMENT_NOTIF":
        // Show tournament notification
        const newNotification = {
          id: Date.now(),
          content: lastMessage.content || "Tournament update",
          timestamp: Date.now(),
        };
        setTournamentNotifications((prev) => [...prev, newNotification]);
        
        // Auto-remove notification after 5 seconds
        setTimeout(() => {
          setTournamentNotifications((prev) =>
            prev.filter((n) => n.id !== newNotification.id)
          );
        }, 5000);
        break;
      case "GAME_INVITE":
        console.log("Game Invite:", lastMessage.content);
        break;
      case "STATUS_UPDATE":
        const userId = (lastMessage as any).userId;
        console.log(
          `User ${userId} is ${lastMessage.isOnline ? "online" : "offline"}`,
        );
        break;
    }
  }, [lastMessage]);
  
  // Function to manually dismiss notification
  const dismissNotification = (id: number) => {
    setTournamentNotifications((prev) => prev.filter((n) => n.id !== id));
  };

  if (loading) {
    return (
      <div className="flex min-h-screen items-center justify-center">
        <Spinner size="xl" />
      </div>
    );
  }

  return (
    <>
      <Navbar fluid className="navbar-custom px-4 sm:px-6 lg:px-8 py-2 z-50 relative">
        <NavbarBrand
          as={Link}
          to="/"
          className="neon-text-purple neon-pulse tracking-neon-wide font-bold"
        >
          🏓{" "}
          <span className="sr-only text-lg sm:not-sr-only md:text-2xl">
            Ping Pong
          </span>
        </NavbarBrand>
        <div className="flex items-center gap-2 text-xs sm:text-base md:order-2">
          {isAuthenticated && user ? (
            <Dropdown
              arrowIcon={false}
              inline
              label={
                <span className="inline-block">
                  <img 
                    src={user.avatar || "/public/avatar.png"} 
                    alt={user.display_name} 
                    className="h-8 w-8 sm:h-9 sm:w-9 rounded-full object-cover border-2 border-gray-300 dark:border-gray-600" 
                    onError={(e) => {
                      const target = e.target as HTMLImageElement;
                      if (target.src !== window.location.origin + "/public/avatar.png") {
                        target.src = "/public/avatar.png";
                      }
                    }}
                  />
                </span>
              }
            >
              <DropdownHeader>
                <span className="block text-xs font-normal">
                  {t("dropdownUser.displayName")}
                </span>
                <span className="block text-sm font-black">
                  {user.display_name}
                </span>
                <span className="block text-xs font-normal">{user.email}</span>
              </DropdownHeader>
              <DropdownDivider />
              <DropdownItem onClick={() => navigate("/settings")}>
                {t("dropdownUser.settings")}
              </DropdownItem>
              <DropdownItem onClick={() => navigate("/friends")}>
                {t("dropdownUser.friends")}
              </DropdownItem>
			  <DropdownItem onClick={() => navigate("/profile")}>
                {t("dropdownUser.profile")}
              </DropdownItem>
              <DropdownDivider />
              <DropdownItem onClick={logout}>
                {t("dropdownUser.logout")}
              </DropdownItem>
            </Dropdown>
          ) : (
            <Button
              className="neon-btn neon-btn-light tracking-neon text-xs sm:text-base px-3 sm:px-4 py-1 sm:py-2"
              onClick={() => setOpenModal(true)}
            >
              {t("login.button")}
            </Button>
          )}

          <Modal
            show={openModal}
            size="md"
            popup
            onClose={() => setOpenModal(false)}
          >
            <ModalHeader />
            <ModalBody>
              <div className="space-y-6">
                <h3 className="neon-text-purple flex justify-center text-lg font-bold">
                  {t("modal.head")}
                </h3>

                {/* OAuth 42 Button */}
                <div className="flex justify-center">
                  <Button
                    className="bg-gradient-to-br from-purple-600 to-blue-500 text-white hover:bg-gradient-to-bl focus:ring-blue-300 dark:focus:ring-blue-800"
                    onClick={() => {
                      setOpenModal(false);
                      login();
                    }}
                  >
                    {t("modal.loginWith")}
                    <img
                      className="ml-4 h-4 w-4"
                      src="/logo42.png"
                      alt="42 Logo"
                    />
                  </Button>
                </div>

                <hr />

                {/* Local Login Form */}
                <form onSubmit={handleLocalLogin}>
                  {error && (
                    <div className="mb-4 rounded border border-red-200 bg-red-50 p-2 text-sm text-red-500 dark:border-red-800 dark:bg-red-900/20">
                      {error}
                    </div>
                  )}

                  <div className="mb-4">
                    <Label htmlFor="email">{t("modal.email")}</Label>
                    <TextInput
                      id="email"
                      type="email"
                      value={email}
                      onChange={(e) => setEmail(e.target.value)}
                      placeholder="name@company.com"
                      required
                      disabled={isSubmitting}
                    />
                  </div>

                  <div className="mb-4">
                    <Label htmlFor="password">{t("modal.password")}</Label>
                    <TextInput
                      id="password"
                      type="password"
                      value={password}
                      onChange={(e) => setPassword(e.target.value)}
                      required
                      disabled={isSubmitting}
                    />
                  </div>


                  <div className="mb-4 w-full">
                    <Button
                      type="submit"
                      className="neon-btn neon-btn-light tracking-neon w-full"
                      disabled={isSubmitting}
                    >
                      {isSubmitting ? "Logging in..." : t("modal.login")}
                    </Button>
                  </div>
                </form>

                <div className="flex justify-between text-sm font-medium text-gray-500 dark:text-gray-300">
                  {t("modal.notRegistered")}
                  <Link
                    to="/register"
                    onClick={() => setOpenModal(false)}
                    className="navbar-link-active"
                  >
                    {t("modal.register")}
                  </Link>
                </div>
              </div>
            </ModalBody>
          </Modal>

					<LanguageSwitcher />
					<DarkThemeToggle mode="auto" className="dark-theme-toggle h-10 w-10 tracking-neon text-lg sm:text-2xl" />
					<NavbarToggle className="text-neon-purple" />
				</div>

        <NavbarCollapse>
          <NavbarLink
            as={Link}
            to="/"
            className={`navbar-link-custom block px-2 py-2 sm:px-3 sm:py-2 ${isActive("/") ? "navbar-link-active" : ""}`}
          >
            {t("menu.home")}
          </NavbarLink>
          <NavbarLink
            as={Link}
            to="/game/chose"
            className={`navbar-link-custom ${isActive("/game/chose") ? "navbar-link-active" : ""}`}
          >
            {t("menu.games")}
          </NavbarLink>
          {/* Tournament menu removed: accessible from game pages */}
        </NavbarCollapse>
      </Navbar>

      <main className="main-content px-4 sm:px-6 lg:px-8">
        <Outlet />
      </main>

      {/* Tournament Notifications Toast Container */}
      <div className="fixed top-20 right-4 z-50 flex flex-col gap-2 max-w-xs">
        {tournamentNotifications.map((notification) => (
          <Toast key={notification.id} className="shadow-lg">
            <div className="inline-flex h-8 w-8 shrink-0 items-center justify-center rounded-lg bg-purple-100 text-purple-500 dark:bg-purple-800 dark:text-purple-200">
              <HiExclamation className="h-5 w-5" />
            </div>
            <div className="ml-3 text-sm font-normal flex-1">
              <span className="mb-1 block text-sm font-semibold text-gray-900 dark:text-white">
                🏆 Tournament Notification
              </span>
              <div className="text-sm font-normal text-gray-700 dark:text-gray-300">
                {notification.content}
              </div>
            </div>
            <button
              type="button"
              className="ml-auto -mx-1.5 -my-1.5 rounded-lg p-1.5 text-gray-400 hover:text-gray-900 hover:bg-gray-100 dark:text-gray-500 dark:hover:text-white dark:hover:bg-gray-700"
              onClick={() => dismissNotification(notification.id)}
              aria-label="Close"
            >
              <HiX className="h-5 w-5" />
            </button>
          </Toast>
        ))}
      </div>
    </>
  );
}

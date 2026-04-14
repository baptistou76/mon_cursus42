import { Link } from "react-router";
import { Button, Card } from "flowbite-react";
import { useAuth } from "../context/AuthContext";
import { useTranslation } from "react-i18next";
import { useLoginModal } from "../context/LoginModalContext";

export default function Home() {
  const { user } = useAuth();
  const { t } = useTranslation();
  const { openModal } = useLoginModal();

  const MenuCard = ({ title, desc, link, btnText, color, onClick }: any) => (
    <Card className="max-w-sm w-full h-full flex flex-col border-gray-200 dark:border-gray-700 bg-white dark:bg-gray-800 hover:bg-gray-50 dark:hover:bg-gray-700 transition-colors duration-300">
      <h5 className="text-2xl font-bold tracking-tight text-gray-900 dark:text-white">
        {title}
      </h5>
      <p className="font-normal text-gray-600 dark:text-gray-400 flex-grow">
        {desc}
      </p>
      {onClick ? (
        <Button onClick={onClick} className={`w-full ${color === 'cyan' ? 'btn-cyan' : 'btn-purple'} font-bold mt-auto`}>
          {btnText}
        </Button>
      ) : (
        <Link to={link} className="mt-auto">
          <Button className={`w-full ${color === 'cyan' ? 'btn-cyan' : 'btn-purple'} font-bold`}>
            {btnText}
          </Button>
        </Link>
      )}
    </Card>
  );

  return (
    <div className="min-h-[80vh] flex flex-col items-center justify-center p-4">
      {/* HERO SECTION */}
      <div className="text-center mb-12 max-w-2xl animate-fade-in-down">
        <h1 className="mb-4 text-4xl font-extrabold tracking-tight leading-none text-gray-900 dark:text-white md:text-5xl lg:text-6xl">
          <span className="text-transparent bg-clip-text bg-gradient-to-r from-purple-400 to-pink-600">
            FT_TRANSCENDENCE
          </span>
        </h1>
        <p className="mb-8 text-lg font-normal text-gray-700 dark:text-gray-300 lg:text-xl sm:px-16 xl:px-48">
          {t("home.hero.subtitle")}
        </p>
      </div>

      {/* CONDITIONAL CONTENT */}
      {user ? (
        <div className="grid gap-6 grid-cols-1 md:grid-cols-2 lg:grid-cols-3 w-full max-w-5xl place-items-center md:place-items-stretch">
          <MenuCard 
            title={t("home.cards.arena.title")}
            desc={t("home.cards.arena.description")}
            link="/game/chose"
            btnText={t("home.cards.arena.button")}
            color="cyan"
          />
          <MenuCard 
            title={t("home.cards.community.title")}
            desc={t("home.cards.community.description")}
            link="/chat"
            btnText={t("home.cards.community.button")}
            color="purple"
          />
          <MenuCard 
            title={t("home.cards.profile.title")}
            desc={t("home.cards.profile.description")}
            link="/profile"
            btnText={t("home.cards.profile.button")}
            color="cyan"
          />
        </div>
      ) : (
        <div className="flex flex-col md:flex-row gap-6 w-full max-w-3xl justify-center items-center md:items-stretch">          
          <div className="w-full max-w-sm md:flex-1">
            <MenuCard 
              title={t("home.cards.register.title")}
              desc={t("home.cards.register.description")}
              link="/register"
              btnText={t("home.cards.register.button")}
              color="purple"
            />
          </div>
        </div>
      )}
    </div>
  );
}
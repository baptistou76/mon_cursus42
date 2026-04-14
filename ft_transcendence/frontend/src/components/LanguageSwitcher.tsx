import { useTranslation } from "react-i18next";
import { Button } from "flowbite-react";
import { Globe } from "lucide-react";

export default function LanguageSwitcher() {
  const { i18n } = useTranslation();
  const changeLanguage = (lng: string) => {
    i18n.changeLanguage(lng);
  };

  const currentLanguage = i18n.language;

  return (
    <Button
      color="light"
      size="sm"
      onClick={() => changeLanguage(currentLanguage === 'en-US' ? 'fr' : (currentLanguage === 'fr' ? 'ru' : 'en-US'))}
     className="neon-btn neon-btn-light tracking-neon h-10"
	 
	 
    >
      <Globe className="w-4 h-5 me-1" />
      {currentLanguage === 'en-US' ? ' EN' : (currentLanguage === 'fr' ? ' FR' : ' РУ')}
    </Button>
  );
}

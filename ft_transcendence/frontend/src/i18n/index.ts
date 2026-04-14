import i18n from "i18next";
import { initReactI18next } from "react-i18next";
import LanguageDetector from "i18next-browser-languagedetector";

import enCommon from "../locales/en.json";
import frCommon from "../locales/fr.json";
import ruCommon from "../locales/ru.json";

const resources = {
  en: {
    common: enCommon, 
  },
  ru: {
    common: ruCommon,
  },
  fr: {
    common: frCommon,
  },
};

i18n
  .use(LanguageDetector)
  .use(initReactI18next)
  .init({
    resources,
    fallbackLng: "en",
    debug: false,

    detection: {
      order: ["querystring", "cookie", "localStorage", "navigator"],
      caches: ["localStorage", "cookie"],
    },

    interpolation: {
      escapeValue: false,
    },

    defaultNS: "common",
  });

export default i18n;

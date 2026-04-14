import { useTranslation } from "react-i18next";
export default function NotFound() {
  const { t } = useTranslation("common");
  return (
    <div>
      <h2>404 - Not Found</h2>
      <p>{t("system.error.http404")}</p>
    </div>
  );
}

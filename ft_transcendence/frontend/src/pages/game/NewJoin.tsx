import Btn from "./GameMenuButton.tsx";
import { useTranslation } from 'react-i18next';

export default function NewJoin() {
	const { t } = useTranslation();		
	return (
		<div className="grid grid-cols-1 items-center content-stretch gap-4 place-items-center">
			<div className="grid grid-cols-1 md:grid-cols-2 gap-10 m-20">
				<Btn to="/game/new" label={t("menu.new_game")} />
				<Btn to="/game/join" label={t("menu.join_game")} />
			</div>
		</div>
	);
}

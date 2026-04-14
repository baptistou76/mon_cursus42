import { Button } from "flowbite-react";
import { Link } from "react-router"; 

export default function GameMenuButton(item) {
	return (
		<Button as={Link} onClick={item.onclick} to={item.to} className="w-42 h-42 md:w-48 md:h-48  lg:w-52 lg:h-52  xl:w-64 xl:h-64  2xl:w-72 2xl:h-72 neon-btn neon-btn-light tracking-neon text-xs sm:text-base rounded-lg">{item.label}</Button>
	);
}

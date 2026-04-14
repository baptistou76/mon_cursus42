const server = process.env.SERVER_IP || "localhost";
const wsUri = "ws://" + server + ":8443/game-api/";

let websocket = null;
let pingInterval;
let counter = 0;

const logElement = document.querySelector("#log");
function log(text) {
	logElement.innerText = `${logElement.innerText}${text}\n`;
	logElement.scrollTop = logElement.scrollHeight;
}

window.addEventListener("pageshow", () => {
	log("OPENING");

	websocket = new WebSocket(wsUri);

	websocket.addEventListener("open", () => {
		log("CONNECTED");
		pingInterval = setInterval(() => {
			log(`SENT: ping: ${counter}`);
			websocket.send("ping");
		}, 1000);
	});

	websocket.addEventListener("close", () => {
		log("DISCONNECTED");
		clearInterval(pingInterval);
	});

	websocket.addEventListener("message", (e) => {
		log(`RECEIVED: ${e.data}: ${counter}`);
		counter++;
	});

	websocket.addEventListener("error", (e) => {
		log(`ERROR: ${e.data}`);
	});
});

window.addEventListener("pagehide", () => {
	if (websocket) {
		log("CLOSING");
		websocket.close();
		websocket = null;
		window.clearInterval(pingInterval);
	}
});

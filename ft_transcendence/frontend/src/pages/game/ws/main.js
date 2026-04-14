async function createResponse(path, mimeType) {
	const file = await Deno.open(path, { read: true });
	const response = new Response(file.readable);
	response.headers.set("Content-Type", mimeType);
	return response;
}

Deno.serve({
	port: 8080,
	async handler(request) {
		if (request.headers.get("upgrade") !== "websocket") {
			const url = new URL(request.url);
			switch (url.pathname) {
				case "/client.js":
					return await createResponse("./client.js", "text/javascript");
				case "/client.css":
					return await createResponse("./client.css", "text/css");
				case "/":
					return await createResponse("./index.html", "text/html");
				default:
					return new Response("Not found", {
						status: 404,
					});
			}
		}
		const { socket, response } = Deno.upgradeWebSocket(request);

		socket.onopen = () => {
			console.log("CONNECTED");
		};
		socket.onmessage = (event) => {
			console.log(`RECEIVED: ${event.data}`);
			socket.send("pong");
		};
		socket.onclose = () => console.log("DISCONNECTED");
		socket.onerror = (error) => console.error("ERROR:", error);

		return response;
	},
});

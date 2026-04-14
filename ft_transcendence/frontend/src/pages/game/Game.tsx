import { useEffect, useContext } from "react";
import { useNavigate } from "react-router";
import { useTranslation } from 'react-i18next';
import { useThemeMode } from "flowbite-react";
import { GameContext } from "../../context/GameContext";
import { TournamentContext } from "../../context/TournamentContext";

export default function Game() {
	const navigate = useNavigate();
	const { t } = useTranslation();
	const { mode } = useThemeMode();
	const gameCtx = useContext(GameContext);
	const tournament = useContext(TournamentContext);
	const fontname = "Orbitron, Arial, sans-serif";
	const trimStr = (s:string) => {
		return (s.length > 10 ? (s.slice(0, 10) + "...") : s);
	};
	const left_player_name  = gameCtx.left_player.name ? gameCtx.left_player.name : "Anonymous";
	const right_player_name = gameCtx.right_player.name ? gameCtx.right_player.name : "Anonymous";

	useEffect(() => {
		let disposed = false;
		try {
			if ((gameCtx as any)?.is_tournament) {
				const stored = JSON.parse(localStorage.getItem("pong.match.ctx") || "{}");
				if (!(gameCtx as any).match_id && stored.match_id) (gameCtx as any).match_id = stored.match_id;
				if (!(gameCtx as any).left_player?.name && stored.left_player_name) (gameCtx as any).left_player = { name: stored.left_player_name } as any;
				if (!(gameCtx as any).right_player?.name && stored.right_player_name) (gameCtx as any).right_player = { name: stored.right_player_name } as any;
				if (!(gameCtx as any).match_id || !(gameCtx as any).left_player?.name || !(gameCtx as any).right_player?.name) {
					console.warn("Missing tournament context, returning to table");
					navigate("/game/tournament_table");
					return;
				}
			}
		} catch {}
		const canvas = (document.getElementById("gameCanvas") as HTMLCanvasElement);
		const ctx = canvas.getContext("2d");

		const isMobile = window.innerWidth < 768;
		const width = isMobile 
			? Math.min(window.innerWidth - 10, 500) 
			: window.innerWidth - 30;
		const height = isMobile 
			? Math.min(window.innerHeight - 80, 600) 
			: window.innerHeight - 120;
			
		canvas.width = width;
		canvas.height = height;

		const scale = isMobile ? 0.7 : 1;
		const fontScale = isMobile ? 0.7 : 1;
		
		ctx.font = Math.round(30 * fontScale) + "px " + fontname;
		ctx.textRendering = "optimizeSpeed";
		ctx.textAlign = "center";

		const padWidth = 0.02;
		const padLength = 0.25;
		const ballRadius = 0.025;
		const space = 0.02;
		const init_speed = 0.005;
		var fps = 0;
		var lastRun = 0;

		function drawRoundRect(x, y, w, h, r) {
			if (ctx.roundRect != undefined)
				ctx.roundRect(x, y, w, h, r);
			else
			{
				ctx.beginPath();
				ctx.moveTo(x, y + r);
				ctx.arcTo(x, y + h, x + r, y + h, r);
				ctx.arcTo(x + w, y + h, x + w, y + h - r, r);
				ctx.arcTo(x + w, y, x + w - r, y, r);
				ctx.arcTo(x, y, x, y + r, r);
				ctx.stroke();
			}
		}
		function color(a, b) {
			const theme = mode;
			if (theme === "auto") {
				if (window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches)
					return a;
				return b;
			} else if (theme === "dark")
				return a;
			else
				return b;
		}
		class Scene {
			constructor() {
				this.drawPending = false;
				this.redraw = (timestamp) => {
					if (disposed) return;
					this.drawPending = false;
					if (!game.startTime)
						game.startTime = performance.now();
					const interval = Math.round((timestamp - game.startTime) % 1016);
					if (!game.over && interval <= 16) {
						if (lpad.ai) lpad.aiUpdateY();
						if (rpad.ai) rpad.aiUpdateY();
					}
					const delta = (timestamp - lastRun) / 1000;
					fps = Math.abs(Math.round(1/delta));
					lastRun = performance.now();
					
					this.drawScene();
					if (!game.over && !disposed) {
						game.requestID = window.requestAnimationFrame(this.redraw);
					}
				};
				this.requestRedraw = () => {
					if (!this.drawPending && !game.over && !disposed) {
						this.drawPending = true;
						game.requestID = window.requestAnimationFrame(this.redraw);
					}
				};
			}
			drawScene() {
				ctx.fillStyle = color("#111827","#f9fafb");
				ctx.fillRect(0, 0, width, height);
				ctx.clearRect(0, 0, width, height); 
				for (const obj of objects) {
					obj.draw();
					if (!game.over) {
						obj.update();
						obj.collisionDetect();
					}
				}
				game.drawScore();
				if (game.breakOut) {
					brickWall.draw();
					if (!game.over) {
						brickWall.collisionDetect();
					}
				}
				else {
					game.drawNet();
				}
				if (game.debug) {
					game.drawDebugInfo();
					const ballRadiusPx = ball.radius * Math.min(width, height);
					if (rpad.ai && rpad.calculated > 0)
						game.drawTargetBall(rpad.x * width - 13, rpad.calculated * height, Math.max(ballRadiusPx - 6, 2));

					if (lpad.ai && lpad.calculated > 0)
						game.drawTargetBall(lpad.x * width + padWidth * width + 13, lpad.calculated * height, Math.max(ballRadiusPx - 6, 2));
				}
				if (game.over)
					btn.draw();
			}
		};
		class Audio {
			audioCtx;
			constructor() {
				this.audioCtx = null;
			}
			ensureContext() {
				if (!this.audioCtx) {
					this.audioCtx = new (window.AudioContext || window.webkitAudioContext)();
				}
				if (this.audioCtx.state === 'suspended') {
					this.audioCtx.resume().catch(() => {});
				}
				return this.audioCtx.state === 'running';
			}
			playHitPad() {
				if (!this.ensureContext()) return;
				const oscillator = new OscillatorNode(this.audioCtx,{frequency: "600", type: "sine"});
				oscillator.frequency.exponentialRampToValueAtTime(800, this.audioCtx.currentTime + 0.05);
				oscillator.frequency.exponentialRampToValueAtTime(1000, this.audioCtx.currentTime + 0.15);
				const gainNode = this.audioCtx.createGain();
				gainNode.gain.exponentialRampToValueAtTime(0.01, this.audioCtx.currentTime + 0.3);
				const successFilter = new BiquadFilterNode(this.audioCtx, {Q: 0.01});
				oscillator
					.connect(successFilter)
					.connect(gainNode)
					.connect(this.audioCtx.destination);
					oscillator.start();
					oscillator.stop(this.audioCtx.currentTime + 0.1);
			}			
			playHitBrick() {
				if (!this.ensureContext()) return;
				const oscillator = new OscillatorNode(this.audioCtx,{frequency: "400", type: "sine"});
				oscillator.frequency.exponentialRampToValueAtTime(200, this.audioCtx.currentTime + 0.05);
				oscillator.frequency.exponentialRampToValueAtTime(100, this.audioCtx.currentTime + 0.2);
				const gainNode = this.audioCtx.createGain();
				gainNode.gain.exponentialRampToValueAtTime(0.01, this.audioCtx.currentTime + 0.3);
				oscillator.connect(gainNode).connect(this.audioCtx.destination);
				oscillator.start();
				oscillator.stop(this.audioCtx.currentTime + 0.1);
			}
			playLost() {
				if (!this.ensureContext()) return;
				const oscillator = new OscillatorNode(this.audioCtx,{frequency: "48", type: "sine"});
				oscillator.frequency.exponentialRampToValueAtTime(200, this.audioCtx.currentTime + 0.05);
				oscillator.frequency.exponentialRampToValueAtTime(100, this.audioCtx.currentTime + 0.9);
				const gainNode = this.audioCtx.createGain();
				gainNode.gain.exponentialRampToValueAtTime(0.01, this.audioCtx.currentTime + 0.3);
				oscillator.connect(gainNode).connect(this.audioCtx.destination);
				oscillator.start();
				oscillator.stop(this.audioCtx.currentTime + 0.3);
			}
		}
		class Game {
			constructor(game_type, leftPlayer, rightPlayer) {

				this.over = false;
				this.resultSubmitted = false; 
				this.scoreL = 0;
				this.scoreR = 0;
				this.max_lives = 5;
				this.lifeL = this.max_lives;
				this.lifeR = this.max_lives;
				this.playerL = leftPlayer;
				this.playerR = rightPlayer;
				this.lifeBallRadius = 0.015; 
				this.maxRounds = 10;
				this.breakOut = (game_type == 2) ? true : false;
				this.debug = false;
				this.requestID = window.requestAnimationFrame(scene.redraw);
				this.paused = false;
				console.log(this.playerL + " vs. " + this.playerR);
			}
			drawScore() {
				ctx.save();
				ctx.shadowColor = "transparent";
				ctx.shadowBlur = 0;
				ctx.shadowOffsetX = 0;
				ctx.shadowOffsetY = 0;

				ctx.font = Math.round(32 * fontScale) + "px " + fontname;
				ctx.fillStyle = color("#c4c7cb", "#18191b");
				ctx.strokeStyle = "black";
				ctx.textAlign = "center";
				ctx.fillText(game.scoreL + " : " + game.scoreR, width / 2, 50);
				ctx.strokeText(game.scoreL + " : " + game.scoreR, width / 2, 50);
				ctx.textBaseline = "middle";
				ctx.font = Math.round(20 * fontScale) + "px " + fontname;

				ctx.textAlign = "left";
				ctx.fillText(t("game.player")+" :  " + trimStr(game.playerL), padWidth + space, height-20);
				ctx.textAlign = "right";
				ctx.fillText(t("game.player")+" :  " + trimStr(game.playerR), width - padWidth - space, height-20);
				ctx.restore();
				if (this.breakOut) {
					let row_width = (this.max_lives + 1) * 2 * (this.lifeBallRadius * width + 3);
					this.drawLives(54 + this.lifeBallRadius * width, 40, game.lifeL);
					this.drawLives(width - padWidth * width - row_width - 15, 40, game.lifeR);
				}
			}
			drawLives(x, y, value) {
				for (let i = 0; i < this.max_lives; ++i)
					this.drawBall(x + i * 2 * (this.lifeBallRadius * width + 7), y, this.lifeBallRadius * width, i < value);
			}
			drawTargetBall(x, y, r) {
				ctx.save();
				ctx.lineWidth = 1 ;
				ctx.strokeStyle = color("gray","lightgray");
				ctx.beginPath();
				ctx.arc(x, y, r, 0, Math.PI*2);
				ctx.stroke();
				ctx.closePath();
				ctx.restore();
			}
			drawBall(x, y, r, type) {
				ctx.save();
				ctx.lineWidth = 3 ;
				ctx.beginPath();
				if (type == 1) {
					ctx.arc(x, y, r, 0, Math.PI*2);
					ctx.fillStyle = color("lightgray","black");
					ctx.fill();
				}
				else {
					ctx.strokeStyle = color("lightgray","black");
					ctx.arc(x, y, r - 1.5, 0, Math.PI*2);
					ctx.stroke();
				}
				ctx.closePath();
				ctx.restore();
			}
			drawDebugInfo() {
				let x = width-260; 
				let y = 80;
				ctx.save();
				ctx.font = Math.round(16 * fontScale) + "px " + fontname;
				ctx.textBaseline = "middle";
				ctx.textAlign = "right";
				ctx.fillStyle = color("#c4c7cb","#18191b");	
				ctx.fillText("vx : ", x+50, y+40);
				ctx.fillText((ball.vx * width).toFixed(1), x+100, y+40);
				ctx.fillText("vy : ", x+150, y+40);
				ctx.fillText((ball.vy * height).toFixed(1), x+200, y+40);
				ctx.fillText(" x : ", x+50, y+65);
				ctx.fillText(Math.round(ball.x * width), x+100, y+65);
				ctx.fillText(" y : ", x+150, y+65);
				ctx.fillText(Math.round(ball.y * height), x+200, y+65);
				ctx.fillText("Lx : ", x+50, y+90);
				ctx.fillText(Math.round(lpad.x * width), x+100, y+90);
				ctx.fillText("Ly : ", x+150, y+90);
				ctx.fillText(Math.round(lpad.y * height), x+200, y+90);
				ctx.fillText("Rx : ", x+50, y+115);
				ctx.fillText(Math.round(rpad.x * width), x+100, y+115);
				ctx.fillText("Ry : ", x+150, y+115);
				ctx.fillText(Math.round(rpad.y * height), x+200, y+115);
				let ai_label = lpad.ai ? "L" : "—    ";
				if (rpad.ai)
					ai_label = lpad.ai ? "L + R" : "R";
				ctx.fillText("AI : ", x+50, y+140);
				ctx.fillText(ai_label, x+100, y+140);
				ctx.beginPath();
				ctx.strokeStyle = color("#c4c7cb","#18191b");
				drawRoundRect(x, y+20, 220, 145, 5);
				ctx.stroke();
				ctx.closePath();
				ctx.restore();
			}
			drawNet() {
				ctx.save();
				ctx.lineWidth = 1;
			ctx.strokeStyle = color("#6b7280","#9ca3af");
				ctx.beginPath();
				const w = 5;
				const h = 25;
				const r = 2;
				const x = width/2 - w/2;				
				for (let y = 100; y < height - 100; y += h + 10)
					drawRoundRect(x, y, w, h, r);
				ctx.stroke();
				ctx.restore();
			}

			start() {
				if (game.over) return;
				
				if (!this.breakOut) {
					// Classic Pong: game ends when a player reaches 10 points
					if (this.scoreL >= this.maxRounds || this.scoreR >= this.maxRounds) {
						console.log(`🏁 Pong game ending: ${this.scoreL} : ${this.scoreR} (max: ${this.maxRounds})`);
						console.log(`   Calling stop() - resultSubmitted: ${this.resultSubmitted}, game.over: ${game.over}`);
						this.stop();
					}
				} else {
					if (this.lifeL == 0 || this.lifeR == 0) {
						console.log(`🏁 Breakout game ending: lives ${this.lifeL} : ${this.lifeR}, bricks broken: ${this.scoreL} : ${this.scoreR}`);
						console.log(`   Calling stop() - resultSubmitted: ${this.resultSubmitted}, game.over: ${game.over}`);
						this.stop();
					}
				}
			}
			stop() {
				console.log(`🛑 stop() called - game.over: ${game.over}, resultSubmitted: ${this.resultSubmitted}`);
				if (!game.over) {
					if (this.resultSubmitted) {
						console.warn("⚠️ Game result already submitted, ignoring duplicate stop() call");
						return;
					}
					this.resultSubmitted = true;
					window.cancelAnimationFrame(this.requestID);
					game.over = true;
					try {
						lpad.blocked = true;
						rpad.blocked = true;
						ball.vx = 0; ball.vy = 0;
					} catch {}
					
					const currentLeftPlayer = gameCtx.left_player.name || "Anonymous";
					const currentRightPlayer = gameCtx.right_player.name || "Anonymous";
					
					let winner = "—";
					if (!this.breakOut) {
						// Pong: winner by score
						if (game.scoreL > game.scoreR)
							winner = currentLeftPlayer;
						else if (game.scoreL < game.scoreR)
							winner = currentRightPlayer;
					} else {
						if (game.lifeL > game.lifeR)
							winner = currentLeftPlayer;
						else if (game.lifeL < game.lifeR)
							winner = currentRightPlayer;
						else if (game.scoreL > game.scoreR)
							winner = currentLeftPlayer;
						else if (game.scoreL < game.scoreR)
							winner = currentRightPlayer;
					}

					gameCtx.finished = true;
					gameCtx.winner = winner;

					if (gameCtx.is_tournament) {
						gameCtx.destination = "/game/tournament_table";
					}
					if (gameCtx.is_tournament && (tournament as any)?.id && (tournament as any)?.match?.match_id) {
						const winnerAlias = winner === "—" ? "" : winner;
						const apiUrl = (import.meta as any).env?.VITE_API_URL || 
							process.env.VITE_API_URL || 
							"/api";
						window.cancelAnimationFrame(this.requestID);
						
						fetch(`${apiUrl}/tournaments/${(tournament as any).id}/match`, {
							method: 'POST',
							headers: { 'Content-Type': 'application/json' },
							credentials: 'include',
							body: JSON.stringify({
								match_id: (tournament as any).match.match_id,
								winner: winnerAlias,
								score: { player1: game.scoreL, player2: game.scoreR }
							})
						}).then(res => {
							if (res.ok) {
								console.log("✅ Match result saved successfully");
							} else {
								return res.json().then(data => {
									if (data.error === 'Match already completed') {
										console.warn("⚠️ Match already completed");
									} else {
										console.error("Failed to save match result:", data);
									}
								}).catch(() => {
									console.error("Failed to parse error response");
								});
							}
						}).catch(err => {
							console.error('Match result submit error:', err);
						});
						} else {
							const isAi = (gameCtx as any).ai_mode === 1 || (gameCtx as any).ai_mode === 2;
							const opponentName = isAi ? "AI Bot" : (currentLeftPlayer || "Guest");
							const payload = {
								winner: winner,
								score: { left: game.scoreL, right: game.scoreR },
								opponent_alias: opponentName,
								mode: isAi ? "ai" : "local",
							};

							const apiUrl = (import.meta as any).env?.VITE_API_URL || process.env.VITE_API_URL || "/api";
							fetch(`${apiUrl}/matches`, {
								method: "POST",
								headers: { "Content-Type": "application/json" },
								credentials: "include",
								body: JSON.stringify(payload),
							})
								.then((res) => {
									if (!res.ok) throw new Error(`HTTP ${res.status}`);
									console.log("Casual match saved!");
								})
								.catch((err) => {
									console.error("Failed to save match", err);
								})
								.finally(() => {
								});
						}
					try { localStorage.removeItem("pong.match.ctx"); } catch {}
				}
			}
		}
		class Pad {
			constructor(x, y, color, ai) {
				this.x = x;
				this.y = y;
				this.vy = 0;
				this.color = color;
				this.sizeX = padWidth;
				this.sizeY = padLength;
				this.ai = ai;
				this.calculated = -1;
				this.blocked = false;
				console.log(`Pad created: x=${x.toFixed(2)}, ai=${ai}, blocked=${this.blocked}`);
			}
			draw() {
				this.update();
				ctx.save();
				ctx.beginPath(); ctx.strokeStyle = this.color;
				const px = this.x * width;
				const py = this.y * height;
				const pw = this.sizeX * width;
				const ph = this.sizeY * height;
				drawRoundRect(px, py, pw, ph, pw/2);
				if (this.blocked) { ctx.stroke(); ctx.closePath(); }
				else { ctx.fillStyle = this.color; ctx.fill(); }
				ctx.restore();
			}
			update() {
				if (game.over) return;
				if (!this.blocked) {
					if (this.y + this.sizeY + this.vy < 1 && this.y + this.vy > 0)
						this.y += this.vy;
				}
			}
			updateY(step) {
				if (game.over) return;
				if (!this.blocked) {
					this.vy = step;
					if (this.y + this.sizeY + this.vy < 1 && this.y + this.vy > 0)
						this.y += this.vy;
					this.update();
				}
			}
			calculatePosition() {
				if (!this.blocked && this.ai &&
					((this.x < 0.5 && ball.vx < 0) || (this.x > 0.5 && ball.vx > 0))) {
					let x = ball.x;
					let y = ball.y;
					let vx = ball.vx;
					let vy = ball.vy;
					let r = ball.radius;
					while (x - r > lpad.x + lpad.sizeX && x + r < rpad.x)
					{
						if (y - r < 0 || y + r > 1)
							vy = -vy;
						x += vx;
						y += vy;
					}
					this.calculated = y;
				}
				else
					this.calculated = -1;
			}
			aiUpdateY() {
				if (!this.blocked && this.ai) {
					this.calculatePosition();
					if (this.calculated != -1) {
						const step = 0.015;
						if (this.calculated < this.y)
							this.updateY(-step);
						else if (this.calculated > this.y + this.sizeY && this.calculated < 1)
							this.updateY(step);
						else
							this.updateY(0);
					}
				}
			}
			collisionDetect() {}
		}
		class Ball {
			touched = false;
			lastHit = -1; 
			lastVx; lastVy; lastX; lastY;
			targetX; targetY; 
			lerpFactor = 0.2;
			constructor(x, y, vx0, vy0, col, radius, type) {
				this.x = x;
				this.y = y;
				this.targetX = x;
				this.targetY = y;
				this.vx0 = vx0;
				this.vy0 = vy0;
				this.radius = radius;
				this.nseg = 8;
				this.type = type;
				this.color = color("white", "black");
				this.resetBall();
			}
			draw() {
				ctx.save();
				ctx.lineWidth = 10;
				const paddleColor = color("#9ca3af", "#4b5563");
				ctx.strokeStyle = paddleColor;
				ctx.fillStyle = paddleColor;
				ctx.shadowColor = "transparent";
				ctx.shadowBlur = 0;
				ctx.shadowOffsetX = 0;
				ctx.shadowOffsetY = 0;

				const px = this.x * width;
				const py = this.y * height;
				const pr = this.radius * Math.min(width, height);

				ctx.beginPath();
				if (this.type == 1) {
					ctx.arc(px, py, pr - 5, 0, Math.PI * 2);
					ctx.clip();
					ctx.beginPath();
					ctx.arc(px, py, pr, 0, Math.PI * 2);
					ctx.fill();
				} else {
					ctx.arc(px, py, pr - 7, 0, Math.PI * 2);
					ctx.fill();
				}
				ctx.stroke();
				ctx.restore();
			}
			pauseBall(val) {
				if (val === true) {
					this.lastVx = this.vx;
					this.lastVy = this.vy;
					this.lastX = this.x;
					this.lastY = this.y;
					this.vx = 0;
					this.vy = 0;
				} else {
					this.vx = this.lastVx;
					this.vy = this.lastVy;
					this.x = this.lastX;
					this.y = this.lastY;
				}
			}
			resetBall() {
				this.type = 1;
				this.lastHit = -1;
				if (!game.breakOut) {
					this.x = 0.5;
					this.y = 0.5;
					this.vx = this.rand(2) * this.vx0;
					this.vy = this.rand(2) * Math.max(this.rnd(this.vx0), this.vx0 * 0.8);
				} else  {
					let sign = this.rand(2);
					this.x = 0.5 + sign * 0.15;
					this.y = 0.12;
					this.vx = sign * this.vx0;
					this.vy = Math.max(this.rnd(this.vx0), this.vx0 * 0.8);
				}
				this.targetX = this.x;
				this.targetY = this.y;
			}
			rand(max) {
				return (-1)**(Math.floor(Math.random() * max));
			}
			rnd(max) {
				return Math.floor(Math.random() * max);
			}
			setTargetPosition(x, y) {
				this.targetX = x;
				this.targetY = y;
			}
			lerpToTarget() {
				this.x += (this.targetX - this.x) * this.lerpFactor;
				this.y += (this.targetY - this.y) * this.lerpFactor;
			}
			update() {
				if (game.over) return;
				if (!this.touched && this.x > 1 - this.radius) {
					if (game.breakOut) {
						// Breakout game
						if (game.lifeR > 0) {
							game.lifeR--;
							audio.playLost();
							this.resetBall();
							game.start();
						} else
							this.vx = -this.vx;
					} else {
						game.scoreL++;
						audio.playLost();
						this.resetBall();
						game.start();
					}
				} else if (!this.touched && this.x < this.radius) {
					if (game.breakOut) {
						if (game.lifeL > 0) {
							game.lifeL--;
							audio.playLost();
							this.resetBall();
							game.start();
						} else
							this.vx = -this.vx;
					} else {
						game.scoreR++;
						audio.playLost();
						this.resetBall();
						game.start();
					}
				
				} else if (!this.touched && (this.y + this.radius > 1 || this.y - this.radius < 0))
					this.vy = -this.vy;
				
				this.y += this.vy;
				this.x += this.vx;
				
				this.targetX = this.x;
				this.targetY = this.y;
				
				this.touched = false;
			}

      rebounce(bx, by, bvx, bvy, py) {
        let n = Math.round(Math.abs(by - py) / (padLength / this.nseg));
        let d = Math.sqrt(bvx ** 2 + bvy ** 2);
        let angle = (n * Math.PI) / (this.nseg - 1);
        let vx = -bvx;
        let vy = -Math.round(d * Math.cos(angle) * 1000) / 1000;
        if (vy === 0) vy = (bvy > 0 ? 1 : -1) * 0.0005;
        return [vx, vy];
      }
      collisionDetect() {
				if (!this.touched) {
					if (!lpad.blocked && this.y + this.vy > lpad.y && this.y + this.vy < lpad.y + lpad.sizeY && this.x + this.vx < lpad.x + lpad.sizeX) {
						this.x = lpad.x + lpad.sizeX + 0.001;
						this.lastHit = 0;
						[this.vx, this.vy] = this.rebounce(this.x, this.y, this.vx, this.vy, lpad.y);
						this.vy += Math.abs(lpad.vy) * (this.vy > 0 ? 1 : -1);
						if (Math.abs(this.vx) < 0.05 && Math.abs(this.vx) > 0)
							this.vx += 0.001;
						this.touched = true;
						audio.playHitPad();
					}
					if (!rpad.blocked && this.y + this.vy > rpad.y && this.y + this.vy < rpad.y + rpad.sizeY && this.x + this.vx > rpad.x) {
						this.x = rpad.x - 0.001;
						this.lastHit = 1;
						[this.vx, this.vy] = this.rebounce(this.x, this.y, this.vx, this.vy, rpad.y);
						this.vy += Math.abs(rpad.vy) * (this.vy > 0 ? 1 : -1);
						if (Math.abs(this.vx) < 0.05 && Math.abs(this.vx) > 0)
							this.vx += -0.001;
						this.touched = true;
						audio.playHitPad();
					}
				}
			}
		}
		class Bricks {
			bricks = [];
			brickWidth = 0.025;
			brickHeight = 0.08;
			brickPadding = 0.012;
			real = false;
			brickRowCount = Math.min(Math.floor(0.6 / (this.brickHeight + this.brickPadding)), 12);
			brickColumnCount = Math.min(Math.floor(0.3 / (this.brickWidth + this.brickPadding)), 12);
			brickOffsetTop = this.brickPadding + 0.5 - this.brickRowCount / 2 * (this.brickHeight + this.brickPadding);
			brickOffsetLeft = 0.5 - (this.brickColumnCount * (this.brickWidth + this.brickPadding) - this.brickPadding) / 2;
			constructor(w, h) {
				if (this.real)
					this.brickPadding = 0.006;
				for (let c = 0; c < this.brickColumnCount; c++) {
					this.bricks[c] = [];
					for (let r = 0; r < this.brickRowCount; r++) {
						this.bricks[c][r] = { x: 0, y: 0, status: 1, type: (Math.round(Math.random() * 20) === 20) ? 1 : 0 };
					}
				}
			}
			draw() {
				ctx.save();	
				ctx.lineWidth = 2;
			ctx.strokeStyle = color("#d1d5db","#6b7280");
				let brickY;
				for (let c = 0; c < this.brickColumnCount; c++) {
					for (let r = 0; r < this.brickRowCount; r++) {
						if (this.bricks[c][r].status === 1) {
							let relBrickX = c * (this.brickWidth + this.brickPadding) + this.brickOffsetLeft;
							if (this.real && c % 2 == 0)
								brickY = r * (this.brickHeight + this.brickPadding) + this.brickOffsetTop + this.brickHeight/2;
							else
								brickY = r * (this.brickHeight + this.brickPadding) + this.brickOffsetTop;
							
							this.bricks[c][r].x = relBrickX;
							this.bricks[c][r].y = brickY;
							
							const brickX = relBrickX * width;
							const brickYpx = brickY * height;
							const bw = this.brickWidth * width;
							const bh = this.brickHeight * height;
							
							ctx.beginPath();
							drawRoundRect(brickX, brickYpx, bw, bh, 5);
							ctx.stroke()
							ctx.beginPath();
							if (this.bricks[c][r].type == 1) {
								ctx.save();
								ctx.lineWidth = 2;
							ctx.strokeStyle = color("#6b7280","#9ca3af");
							ctx.shadowColor = color("#f9fafb","#1f2937");
								ctx.shadowBlur = 8;
								ctx.beginPath();
								drawRoundRect(brickX, brickYpx, bw, bh, 5);
								ctx.stroke();
								ctx.restore();
							}
							ctx.stroke();
							ctx.closePath();
						}
					}
				}
				ctx.restore();
			}
			collisionDetect() {
				for (let c = 0; c < this.brickColumnCount; c++) {
					for (let r = 0; r < this.brickRowCount; r++) {
						const b = this.bricks[c][r];
						if (b.status == 0 || ball.lastHit == -1)
							continue;
						if (ball.x > b.x && ball.x < b.x + this.brickWidth && ball.y > b.y && ball.y < b.y + this.brickHeight) {
							ball.vx = -ball.vx;
							b.status = 0;
							if (ball.lastHit == 0 && !lpad.blocked) 
								game.scoreL++;
							else if (ball.lastHit == 1 && !rpad.blocked)
								game.scoreR++;
							audio.playHitBrick();
							if (b.type === 1) {
								ball.type = 2;
								ball.vx += ball.vx > 0 ? 0.015 : -0.015;
							}
						} else 
						if (ball.x > b.x && ball.x < b.x + this.brickWidth && ball.y > b.y && ball.y < b.y + this.brickHeight) {
							ball.vx = -ball.vx;
							b.status = 0;
							if (ball.lastHit == 0 && !lpad.blocked) 
								game.scoreL++;
							else if (ball.lastHit == 1 && !rpad.blocked)
								game.scoreR++;
							audio.playHitBrick();
							if (b.type === 1) {
								ball.type = 2;
								ball.vx += ball.vx > 0 ? 0.015 : -0.015;
							}
						}
					}
				}
			}
		}
		class Button {
			constructor(text, w, h) {
				this.width = w;
				this.height = h;
				this.border = 2;
				this.radius = 20;
				this.text = text;
				this.show_score = true;
				this.y = height/2 - (this.height/2 - 60);
				this.x = width/2 - this.width/2;
			}
			scoreTableClicked(x, y) {
				return ((x > this.x && x < this.x + this.width)
					&& (y > this.y && y < this.y + this.height));
			}
			draw() {
				ctx.save();
				ctx.beginPath();
				drawRoundRect(width/2- this.width/2, height/2-this.height/2, this.width, this.height, this.radius); 
				ctx.fillStyle = color("#1f2937", "#ffffff");
				ctx.fill();
				ctx.textAlign = "center";
				ctx.textBaseline = "middle";
				if (this.show_score)
				{
					let y = height/2 - (this.height/2 - 60);
					let score = game.scoreL + " : " + game.scoreR;
					ctx.save();

					ctx.font = Math.round(24 * fontScale) + "px " + fontname;
					ctx.fillStyle = color("#e5e7eb","#111827");
					ctx.fillText("Score :", width/2, y);
					ctx.fillText("Winner :", width/2, y + 100);

					ctx.font = Math.round(34 * fontScale) + "px " + fontname;
					ctx.fillText(score, width/2, y + 40);
					const winner = trimStr(gameCtx.winner);
					ctx.fillText(winner , width/2, y + 140);
					ctx.font = Math.round(18 * fontScale) + "px " + fontname;
					ctx.fillText("Press space / click here", width/2, y + 220);
					ctx.fillText("to continue", width/2, y + 250);

					ctx.lineWidth = 2;
					ctx.strokeStyle = color("#6b7280","#9ca3af");
					ctx.shadowColor = color("#d1d5db","#374151");
					ctx.shadowBlur = 8;
					ctx.beginPath();
					drawRoundRect(width/2-this.width/2, height/2-this.height/2, this.width, this.height, this.radius);
					ctx.stroke();
					ctx.restore();
				} else {
					this.width = 380;
					this.height = 120;
					ctx.font = Math.round(42 * fontScale) + "px " + fontname;
					ctx.fillStyle = color("#e5e7eb","#111827");
					ctx.fillText(this.text, width/2, height/2+2);
					ctx.strokeText(this.text, width/2, height/2+2);
				}
				ctx.closePath();
				if (this.border == 1) {
					ctx.lineWidth = 2;
					ctx.strokeStyle = color("#9ca3af","#4b5563");
					ctx.beginPath();
					drawRoundRect(width/2-this.width/2, height/2-this.height/2, this.width, this.height, this.radius);
					ctx.stroke();
					ctx.closePath();
				}
				ctx.restore();
			}
		}
		const scene = new Scene();
		const game = new Game(gameCtx.game_type, left_player_name, right_player_name);
		const ball = new Ball(0.5, 0.5, init_speed, init_speed, color("#f3f4f6","#1f2937"), ballRadius, 1);
		const lpad = new Pad(space, 0.5 - padLength/2, color("#9ca3af","#4b5563"), (!gameCtx.is_tournament && gameCtx.ai_mode===1) ? 1 : 0);
		const rpad = new Pad(1 - padWidth - space, 0.5 - padLength/2, color("#9ca3af","#4b5563"), (!gameCtx.is_tournament && gameCtx.ai_mode===2) ? 1 : 0);
		const audio = new Audio();
		const brickWall = new Bricks(width, height);
		const btn = new Button("GAME OVER", 420, 360);

		var objects = [ball, lpad, rpad];
		
		const keyDownHandler = (e) => {
			if (['w', 's', 'ArrowUp', 'ArrowDown', ' ', 'Escape', 'b', 'i', 'j'].includes(e.key)) {
				e.preventDefault();
			}
			const step = 0.015;
			switch (e.key) {
				case "w":
					if (!lpad.ai) lpad.updateY(-step);
					break;
				case "ArrowUp":
					if (!rpad.ai) rpad.updateY(-step);
					break;
				case "s":
					if (!lpad.ai) lpad.updateY(step);
					break;
				case "ArrowDown":
					if (!rpad.ai) rpad.updateY(step);
					break;
				case "b":
					game.breakOut = !game.breakOut;
					break;
				case "i":
					lpad.ai = !lpad.ai;
					break;
				case "j":
					game.debug = !game.debug;
					break;
				case "Escape":
					game.paused = !game.paused;
					ball.pauseBall(game.paused);
					break;
				case " ":
					if (game.over && gameCtx.finished)
						leaveGame();
					break;
			}
		};
		
		const keyUpHandler = (e) => {
			if (['w', 's', 'ArrowUp', 'ArrowDown'].includes(e.key)) {
				e.preventDefault();
			}
			switch (e.key) {
				case "w":
					lpad.updateY(0);
					break;
				case "ArrowUp":
					rpad.updateY(0);
					break;
				case "s":
					lpad.updateY(0);
					break;
				case "ArrowDown":
					rpad.updateY(0);
					break;
			}
		};
		const touchHandler = (e) => {
			try {
				if (e.touches && e.touches.length > 0) {
					e.preventDefault();
					
					if (game.over && gameCtx.finished) {
						console.log("Touch detected on finished game, leaving");
						leaveGame();
						return;
					}
					
					const rect = canvas.getBoundingClientRect();
					const touch = e.touches[0];
					
					const touchX = touch.clientX - rect.left;
					const touchY = touch.clientY - rect.top;
					
					const relX = touchX / width;
					const relY = touchY / height;
					
					console.log("Touch at:", relX.toFixed(2), relY.toFixed(2));
					
					if (relX < 0.5) {
						const newY = Math.max(0, Math.min(1 - lpad.sizeY, relY - lpad.sizeY / 2));
						lpad.y = newY;
						console.log("Moving left paddle to:", newY.toFixed(2));
					} else {
						const newY = Math.max(0, Math.min(1 - rpad.sizeY, relY - rpad.sizeY / 2));
						rpad.y = newY;
						console.log("Moving right paddle to:", newY.toFixed(2));
					}
				}
			} catch (error) {
				console.error("Touch handler error:", error);
			}
		};
		const leaveGame = () => {
			document.removeEventListener("keyup",   keyUpHandler);
			document.removeEventListener("keydown", keyDownHandler);
			document.removeEventListener("touchstart", touchHandler, { passive: false });
			document.removeEventListener("touchmove",  touchHandler, { passive: false });
			document.removeEventListener("click", clickHandler);
			navigate(gameCtx.destination);
		};
		const clickHandler = (e) => {
			if (gameCtx.finished && game.over && btn.scoreTableClicked(e.clientX, e.clientY))
				leaveGame();
		}
		document.addEventListener("keyup",   keyUpHandler);
		document.addEventListener("keydown", keyDownHandler);
		document.addEventListener("touchstart", touchHandler, { passive: false });
		document.addEventListener("touchmove",  touchHandler, { passive: false });
		document.addEventListener("click",   clickHandler);
		scene.requestRedraw();
		game.start();
		
		return () => {
			disposed = true;
			console.log("Game component unmounting, removing event listeners");
			document.removeEventListener("keydown", keyDownHandler);
			document.removeEventListener("keyup", keyUpHandler);
			document.removeEventListener("touchstart", touchHandler, { passive: false });
			document.removeEventListener("touchmove", touchHandler, { passive: false });
			document.removeEventListener("click", clickHandler);
			window.cancelAnimationFrame(game.requestID);
		};
	}, []);
  return (
	<div className="flex items-center justify-center w-full h-full overflow-hidden bg-gray-900">
		<canvas 
			id="gameCanvas" 
			className="max-w-full max-h-full touch-none"
			style={{ display: 'block' }}
		></canvas>
	</div>
  );
}

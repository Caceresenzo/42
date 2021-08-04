<template>
	<div id="app">
		<div v-if="last == 'connect'">je suis connecté</div>

		<div v-else-if="last == 'disconnect'">je suis déconnecté</div>

		<div v-else>état inconnu</div>

		<!-- <div v-for="(message, index) in messages" :key="index">
			{{ message }}
		</div> -->

		{{ paddleX }}

		<button @click="up">++</button>
		<button @click="down">--</button>
	</div>
</template>

<script>
import { io } from "socket.io-client";

let socket;

export default {
	name: "App",
	data: () => ({
		last: null,
		messages: [],
		paddleX: 0,
	}),
	mounted() {
		socket = io("ws://127.0.0.1:3000");
		socket.on("connect", () => {
			this.last = "connect";
		});

		socket.on("disconnect", () => {
			this.last = "disconnect";
		});

		socket.on("message", (message) => {
			this.messages.unshift(message);
		});

		socket.on("position", ({ paddleX }) => {
			this.paddleX = paddleX;
		});
	},
	methods: {
		up() {
			socket.emit("update-position", {
				x: this.paddleX + 1,
			});
		},
		down() {
			socket.emit("update-position", {
				x: this.paddleX - 1,
			});
		},
	},
};
</script>

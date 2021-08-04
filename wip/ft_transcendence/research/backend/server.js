const express = require("express");
const app = express();
const http = require("http");
const server = http.createServer(app);
const { Server } = require("socket.io");

app.use(function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "http://192.168.1.10:8080");
  res.header(
    "Access-Control-Allow-Headers",
    "Origin, X-Requested-With, Content-Type, Accept"
  );
  next();
});

var cors = require("cors");
app.use(cors());

const io = new Server(server, {
  cors: {
    origin: "*",
    methods: ["GET", "POST"],
  },
});

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

class Game {
  constructor(player1, player2) {
    this.connectedPlayer = 0;
    this.intervalId = null;
    this.paddleX = 0;
  }

  start() {
    this.intervalId = setInterval(() => {
      io.emit("position", {
        paddleX: this.paddleX,
      });
    }, 100);
  }

  stop() {
    clearInterval(this.intervalId);
    this.intervalId = null;
  }

  isRunning() {
    return this.intervalId != null
  }
}

let game = new Game();

io.on("connection", function (socket) {
  console.log("a user connected");

  game.connectedPlayer++;

  if (game.connectedPlayer == 2) {
    game.start();
  }

  socket.on("update-position", function ({ x }) {
    if (game.isRunning()) {
      game.paddleX = x;
    }
  });

  socket.on("disconnect", function () {
    console.log("user disconnected");

    game.connectedPlayer--;

    if (game.connectedPlayer != 2) {
      game.stop();
    }
  });
});

server.listen(3000, () => {
  console.log("listening on *:3000");
});

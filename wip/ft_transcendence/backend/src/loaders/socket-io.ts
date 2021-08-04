import * as http from "http";
import * as socketio from "socket.io";
import { Container } from "typedi";
import socketAuthentication from "../middlewares/SocketAuthentication";
import SocketService, { ChannelEvent, GameEvent, MatchMakingEvent } from "../services/SocketService";

export default async ({ server }: { server: http.Server }) => {
  const io = new socketio.Server(server, {
    cookie: false,
    cors: {
      origin: "*",
      methods: ["GET", "POST"],
    },
  });

  Container.set(socketio.Server, io);
  const socketService = Container.get(SocketService);

  io.use(socketAuthentication());

  io.on("connection", (socket) => {
    socketService.onConnect(socket);

    socket.on("disconnect", () => {
      socketService.onDisconnect(socket);
      socketService.askMatchMakingLeave(socket);
      socketService.askGameDisconnect(socket);
    });

    socket.on(ChannelEvent.CONNECT, (body, callback) => {
      socketService.askChannelConnect(socket, body, callback);
    });

    socket.on(ChannelEvent.DISCONNECT, () => {
      socketService.askChannelDisconnect(socket);
    });

    socket.on(GameEvent.CONNECT, (body, callback) => {
      socketService.askGameConnect(socket, body, callback);
    });

    socket.on(GameEvent.DISCONNECT, () => {
      socketService.askGameDisconnect(socket);
    });

    socket.on(GameEvent.MOVE, (body, callback) => {
      socketService.askGameMove(socket, body, callback);
    });

    socket.on(MatchMakingEvent.WAITING_ROOM_JOIN, (body, callback) => {
      socketService.askMatchMakingJoin(socket, body, callback);
    });

    socket.on(MatchMakingEvent.WAITING_ROOM_LEAVE, () => {
      socketService.askMatchMakingLeave(socket);
    });
  });
};

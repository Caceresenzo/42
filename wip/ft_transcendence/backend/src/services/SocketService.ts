import * as socketio from "socket.io";
import { Socket } from "socket.io";
import Container, { Service } from "typedi";
import { isObject } from "util";
import AchievementProgress from "../entities/AchievementProgress";
import Channel from "../entities/Channel";
import ChannelMessage from "../entities/ChannelMessage";
import ChannelUser from "../entities/ChannelUser";
import Relationship from "../entities/Relationship";
import User from "../entities/User";
import Game from "../game/Game";
import ChannelService from "./ChannelService";

export type Callback = (err: Error, answer: any) => void;

export enum ClientEvent {
  CONNECTED_JOIN = "client_connected_join",
  CONNECTED_QUIT = "client_connected_quit",
  CONNECTED_LIST = "client_connected_list",
  PLAYING_JOIN = "client_playing_join",
  PLAYING_QUIT = "client_playing_quit",
  PLAYING_LIST = "client_playing_list",
}

export enum ChannelEvent {
  CONNECT = "channel_connect",
  DISCONNECT = "channel_disconnect",
  UPDATE = "channel_update",
  DELETE = "channel_delete",
  MESSAGE = "channel_message",
  EDIT_MESSAGE = "channel_message_update",
  MESSAGE_DELETE = "channel_message_delete",
  MESSAGE_DELETE_ALL = "channel_message_delete_all",
  USER_JOIN = "channel_user_join",
  USER_LEAVE = "channel_user_leave",
  USER_UPDATE = "channel_user_update",
  OWNER_TRANSFER = "channel_owner_transfer",
  NEW = "channel_new",
  ADD = "channel_add",
}

export enum DirectMessageEvent {
  ADD = "direct_message_add",
}

export enum GameEvent {
  CONNECT = "game_connect",
  DISCONNECT = "game_disconnect",
  MOVE = "game_move",
  STARTING = "game_starting",
}

export enum MatchMakingEvent {
  WAITING_ROOM_JOIN = "waiting_room_join",
  WAITING_ROOM_LEAVE = "waiting_room_leave",
}

export enum UserEvent {
  RELATIONSHIP_NEW = "relationship_new",
  RELATIONSHIP_UPDATE = "relationship_update",
  RELATIONSHIP_DELETE = "relationship_delete",
}

export enum AchievementEvent {
  UNLOCK = "achievement_unlock",
}

export type Event =
  | ClientEvent
  | ChannelEvent
  | DirectMessageEvent
  | GameEvent
  | UserEvent
  | AchievementEvent;

class SessionCounter {
  sessions: { [key: number]: number } = {};

  constructor(
    private readonly io: socketio.Server,
    private readonly joinEvent: ClientEvent,
    private readonly quitEvent: ClientEvent,
    private readonly listEvent: ClientEvent,
    private readonly notifySelf: boolean = false
  ) {}

  onJoin(socket: Socket) {
    const { user } = socket.data as { user: User };
    const { id } = user;

    if (this.sessions[id]) {
      this.sessions[id] += 1;
    } else {
      socket.broadcast.emit(this.joinEvent, id);

      this.sessions[id] = 1;
    }

    this.emitSessons(socket);
  }

  onQuit(socket: Socket) {
    const user: User = socket.data.user;

    this.onUserQuit(user, socket);
  }

  onUserQuit(user: User, socket?: Socket) {
    const { id } = user;

    if (this.sessions[id]) {
      const now = (this.sessions[id] -= 1);

      if (now === 0) {
        if (this.notifySelf) {
          this.io.emit(this.quitEvent, id);
        } else {
          if (socket) {
            socket.broadcast.emit(this.quitEvent, id);
          }
        }

        delete this.sessions[id];
      }
    }
  }

  emitSessons(socket: Socket) {
    socket.emit(this.listEvent, this.connectedIds);
  }

  get connectedIds() {
    return Object.keys(this.sessions);
  }
}

@Service()
export default class SocketService {
  private get gameService(): any {
    return Container.get(require("./GameService").default);
  }
  private get matchMakingService(): any {
    return Container.get(require("./MatchMakingService").default);
  }
  private channelService = Container.get(ChannelService);

  get io() {
    return Container.get(socketio.Server);
  }

  private _connectedUsers?: SessionCounter;
  get connectedUsers(): SessionCounter {
    if (!this._connectedUsers) {
      this._connectedUsers = new SessionCounter(
        this.io,
        ClientEvent.CONNECTED_JOIN,
        ClientEvent.CONNECTED_QUIT,
        ClientEvent.CONNECTED_LIST
      );
    }

    return this._connectedUsers;
  }

  private _playingUsers?: SessionCounter;
  get playingUsers(): SessionCounter {
    if (!this._playingUsers) {
      this._playingUsers = new SessionCounter(
        this.io,
        ClientEvent.PLAYING_JOIN,
        ClientEvent.PLAYING_QUIT,
        ClientEvent.PLAYING_LIST,
        true
      );
    }

    return this._playingUsers;
  }

  onConnect(socket: Socket) {
    this.connectedUsers.onJoin(socket);
    this.playingUsers.emitSessons(socket);

    const user: User = socket.data.user;
    socket.join(user.toRoom());
  }

  onDisconnect(socket: any) {
    this.connectedUsers.onQuit(socket);

    this.matchMakingService.remove(socket);
  }

  async askChannelConnect(socket: Socket, body: any, callback: Callback) {
    const { currentChannelRoom } = socket.data;

    try {
      this.ensureBody(body);

      const { channelId } = body;

      const channel = await this.channelService.findById(channelId);

      if (!channel) {
        throw new Error("channel not found");
      }

      if (currentChannelRoom !== undefined) {
        socket.leave(currentChannelRoom);
      }

      const newChannelRoom = channel.toRoom();

      socket.join(newChannelRoom);
      socket.data.currentChannelRoom = newChannelRoom;

      callback(null, 1);
    } catch (error) {
      callback(error, null);
    }
  }

  askChannelDisconnect(socket: Socket) {
    const { currentChannelRoom } = socket.data;

    if (currentChannelRoom !== undefined) {
      socket.leave(currentChannelRoom);
    }

    delete socket.data.currentChannelRoom;
  }

  public broadcastChannelUpdate(channel: Channel, users: Array<User>) {
    this.broadcastToChannel(channel, ChannelEvent.UPDATE, channel);
    this.broadcastToUsers(users, ChannelEvent.UPDATE, channel);
  }

  public broadcastChannelDelete(channel: Channel) {
    this.broadcastToChannel(channel, ChannelEvent.DELETE, channel);
  }

  public async broadcastChannelMessage(message: ChannelMessage) {
    const channel = await message.channel;

    this.broadcastToChannel(channel, ChannelEvent.MESSAGE, message);
  }

  public async broadcastChannelEditMessage(message: ChannelMessage) {
    const channel = await message.channel;

    this.broadcastToChannel(channel, ChannelEvent.EDIT_MESSAGE, message);
  }

  public async broadcastChannelMessageDelete(message: ChannelMessage) {
    const channel = await message.channel;

    this.broadcastToChannel(channel, ChannelEvent.MESSAGE_DELETE, message);
  }

  public broadcastChannelMessageDeleteAll(channel: Channel) {
    this.broadcastToChannel(channel, ChannelEvent.MESSAGE_DELETE_ALL, channel);
  }

  public broadcastChannelUserJoin(channelUser: ChannelUser) {
    const channel = channelUser.channel;

    this.broadcastToChannel(channel, ChannelEvent.USER_JOIN, channelUser);
  }

  public broadcastChannelUserLeave(channelUser: ChannelUser) {
    const channel = channelUser.channel;

    this.broadcastToChannel(channel, ChannelEvent.USER_LEAVE, channelUser);
  }

  public broadcastChannelUserUpdate(channelUser: ChannelUser) {
    const channel = channelUser.channel;

    this.broadcastToChannel(channel, ChannelEvent.USER_UPDATE, channelUser);
  }

  public broadcastChannelOwnerTransfer(channel: Channel) {
    this.broadcastToChannel(
      channel,
      ChannelEvent.OWNER_TRANSFER,
      channel.owner
    );
  }

  public broadcastUserRelationshipNew(relationship: Relationship) {
    this.broadcastToUser(
      relationship.user,
      UserEvent.RELATIONSHIP_NEW,
      relationship
    );
  }

  public broadcastUserRelationshipUpdate(relationship: Relationship) {
    this.broadcastToUser(
      relationship.user,
      UserEvent.RELATIONSHIP_UPDATE,
      relationship
    );
  }

  public broadcastUserRelationshipDelete(user: User, peer: User) {
    this.broadcastToUser(user, UserEvent.RELATIONSHIP_DELETE, peer);
  }

  public broadcastNewChannel(channel: Channel) {
    // TODO need rework, like only for publics?
    this.io.emit(ChannelEvent.NEW, channel.toJSON());
  }

  public notifyAdded(user: User, channel: Channel) {
    const event = channel.isDirect()
      ? DirectMessageEvent.ADD
      : ChannelEvent.ADD;

    this.broadcastToUser(user, event, channel);
  }

  public notifyAchievementUnlock(
    user: User,
    achievementProgress: AchievementProgress
  ) {
    this.broadcastToUser(user, AchievementEvent.UNLOCK, achievementProgress);
  }

  async askMatchMakingJoin(
    socket: Socket,
    body: { id: number },
    callback: Callback
  ) {
    const pendingGameService = Container.get(
      require("./PendingGameService").default
    ) as any;

    try {
      this.ensureBody(body);
      const { id } = body;

      let pendingGame = undefined;
      if (id) {
        pendingGame = await pendingGameService.findById(id);

        if (!pendingGame) {
          throw new Error(`no pending game found for id = '${id}'`);
        }
      }

      await this.matchMakingService.add(socket, pendingGame);

      callback(null, 1);
    } catch (error) {
      callback(error, null);
    }
  }

  async askMatchMakingLeave(socket: Socket) {
    try {
      this.matchMakingService.remove(socket);
    } catch (error) {
      console.log(error);
    }
  }

  async askGameConnect(socket: Socket, body: any, callback: Callback) {
    await this.askGameDisconnect(socket, true);

    try {
      this.ensureBody(body);

      const { gameId } = body;

      const game = this.gameService.findById(gameId);

      if (!game) {
        throw new Error("game not found");
      }

      const newGameRoom = game.toRoom();

      socket.join(newGameRoom);
      socket.data.currentGameRoom = newGameRoom;

      this.gameService.onConnected(socket);

      callback(null, game.toJSON());
    } catch (error) {
      callback(error, null);
    }
  }

  async askGameDisconnect(socket: Socket, toReconnect = false) {
    const { currentGameRoom } = socket.data;

    if (currentGameRoom !== undefined) {
      socket.leave(currentGameRoom);
      delete socket.data.currentGameRoom;

      this.gameService.onDisconnected(socket);
    }
  }

  async askGameMove(socket: Socket, body: any, callback: Callback) {
    try {
      this.ensureBody(body);

      const { gameId, y } = body;

      if ([gameId, y].includes(undefined)) {
        return callback(new Error("invalid value"), null);
      }

      const success = this.gameService.gameMove(gameId, socket.data.user, y);

      if (!success) {
        throw new Error("invalid position");
      }

      callback(null, y);
    } catch (error) {
      callback(error, null);
    }
  }

  public broadcastGameStarting(game: Game) {
    this.broadcastToGame(game, GameEvent.STARTING, game.toJSON());
  }

  private broadcastToChannel(
    channel: Channel,
    event: ChannelEvent,
    message?: any
  ) {
    this.broadcastToRoom(channel.toRoom(), event, message);
  }

  private broadcastToGame(game: Game, event: GameEvent, message?: any) {
    this.broadcastToRoom(game.toRoom(), event, message);
  }

  private broadcastToUser(user: User, event: UserEvent | Event, message?: any) {
    this.broadcastToRoom(user.toRoom(), event, message);
  }

  private broadcastToUsers(
    users: Array<User>,
    event: UserEvent | Event,
    message?: any
  ) {
    this.broadcastToRoom(
      users.map((x) => x.toRoom()),
      event,
      message
    );
  }

  private broadcastToRoom(
    room: string | Array<string>,
    event: Event,
    message?: any
  ) {
    this.io.to(room).emit(event, message?.toJSON?.() || message);

    console.log(`[io]: {${room}} -> ${event}: ${JSON.stringify(message)}`);
  }

  private ensureBody(body: any) {
    if (!body || !isObject(body)) {
      throw new Error("bad body");
    }
  }
}

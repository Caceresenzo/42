const Dummy = require("./components/dummy");
const Channel = require("./components/channel");
const User = require("./components/user");
const Friendship = require("./components/friendship");

export default {
  "/": {
    group: null,
    view: () => new Dummy.EmptyView(),
  },
  "/channels": {
    group: "channels",
    view: () =>
      new Channel.ChannelListView({
        collection: new Channel.ChannelCollection(),
        fetch: true,
      }),
  },
  "/channel/create": {
    group: "channels",
    view: () => new Channel.ChannelCreateOrEditView({ id: null }),
  },
  "/channel/:id": {
    group: "channels",
    view: (id) => new Channel.ChannelView({ id }),
  },
  "/channel/:id/edit": {
    group: "channels",
    view: (id) => new Channel.ChannelCreateOrEditView({ id }),
  },
  "/channel/:id/join": {
    group: "channels",
    view: (id) => new Channel.ChannelJoinView({ id }),
  },
  "/channel/:id/leave": {
    group: "channels",
    view: (id) => new Channel.ChannelLeaveView({ id }),
  },
  "/channel/:id/transfer-ownership": {
    group: "channels",
    view: (id) => new Channel.ChannelTransferOwnershipView({ id }),
  },
  "/channel/:id/delete": {
    group: "channels",
    view: (id) => new Channel.ChannelDeleteView({ id }),
  },
  "/channel/:id/clear": {
    group: "channels",
    view: (id) => new Channel.ChannelClearView({ id }),
  },
  "/channel/:id/ban/:userid": {
    group: "channels",
    view: (id, userId) => new Channel.ChannelBanUserView({ id, userId }),
  },
  "/channel/:id/unban/:userid": {
    group: "channels",
    view: (id, userId) => new Channel.ChannelUnbanUserView({ id, userId }),
  },
  "/channel/:id/promote/:userid": {
    group: "channels",
    view: (id, userId) => new Channel.ChannelPromoteUserView({ id, userId }),
  },
  "/channel/:id/demote/:userid": {
    group: "channels",
    view: (id, userId) => new Channel.ChannelDemoteUserView({ id, userId }),
  },
  "/channel/:id/add": {
    group: "channels",
    view: (id) => new Channel.ChannelAddUserView({ id }),
  },
  "/channel/:id/remove/:userid": {
    group: "channels",
    view: (id, userId) => new Channel.ChannelRemoveUserView({ id, userId }),
  },
  "/channel/:id/mute/:userid": {
    group: "channels",
    view: (id, userId) =>
      new Dummy.SimpleView({
        template: "script[id='template-channel-mute']",
        data: {
          id,
          userId,
        },
      }),
  },
  "/channel/:id/unmute/:userid": {
    group: "channels",
    view: (id, userId) =>
      new Dummy.SimpleView({
        template: "script[id='template-channel-unmute']",
        data: {
          id,
          userId,
        },
      }),
  },
  "/friendships": {
    group: "friendships",
    view: () => new Friendship.FriendshipListsView({ userId: currentUser.id }),
  },
  "/friendship/add/:user_id": {
    group: "friendships",
    view: (userId) => new Friendship.FriendshipAddView({ userId }),
  },
  "/friendship/accept/:user_id": {
    group: "friendships",
    view: (userId) => new Friendship.FriendshipAcceptView({ userId }),
  },
  "/guilds": {
    group: "guilds",
    view: () => new Dummy.EmptyView(),
  },
  "/profile": {
    group: "profile",
    view: () => new User.UserProfileView({ id: currentUser.id }),
  },
  "/profile/edit": {
    group: "profile",
    view: () => new User.UserProfileEditView(),
  },
  "/users": {
    group: "users",
    view: () =>
      new User.UserListView({
        collection: new User.UserCollection(),
        fetch: true,
      }),
  },
  "/user/:id": {
    group: "users",
    view: (id) => new User.UserProfileView({ id }),
  },
};

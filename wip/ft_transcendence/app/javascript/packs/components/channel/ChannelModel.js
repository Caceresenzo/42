import Backbone from "backbone";

const ChannelModel = Backbone.Model.extend({
  urlRoot: "/api/channels",
  isOwner(user) {
    const owner = this.get("owner");

    if (owner) {
      return owner.id == user.id;
    }

    return false;
  },
  isAdmin(user) {
    return this.getMember(user)?.admin === true;
  },
  isMember(user) {
    return this.getMember(user) != null;
  },
  getMember(user) {
    const members = this.get("members");

    if (members) {
      for (const member of members) {
        if (member.user.id == user.id) {
          return member;
        }
      }
    }

    return null;
  }
});

export default ChannelModel;

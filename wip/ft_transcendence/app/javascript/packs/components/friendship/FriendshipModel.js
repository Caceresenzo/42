import Backbone from "backbone";

const FriendshipModel = Backbone.Model.extend({
  initialize({ user }) {
    this.user = user;
  },
  urlRoot() {
    return `/api/users/${this.user.id}/friends`;
  },
});

export default FriendshipModel;

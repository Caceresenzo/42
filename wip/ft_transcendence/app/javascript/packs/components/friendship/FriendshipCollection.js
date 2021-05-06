import Backbone from "backbone";

import FriendshipModel from "./FriendshipModel";

const ACCEPTED_MODES = ["", "pending", "requests"];

const UserCollection = Backbone.Collection.extend({
  initialize([], { user, mode = "" }) {
    this.user = user;
    this.mode = mode;

    if (!ACCEPTED_MODES.includes(mode)) {
      throw new Exception(`invalid mode: '${mode}'`);
    }
  },
  url() {
    return `/api/users/${this.user.id}/friends/${this.mode}`;
  },
  model: FriendshipModel,
});

export default UserCollection;

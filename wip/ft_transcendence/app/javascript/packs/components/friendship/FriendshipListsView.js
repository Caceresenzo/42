import Backbone from "backbone";
import _ from "underscore";

import { UserModel } from "../user";

import FriendshipCollection from "./FriendshipCollection";
import FriendshipListView from "./FriendshipListView";

const FriendshipListsView = Backbone.View.extend({
  template: _.template($("script[id='template-friendship-lists']").html()),
  events: {
    "click .refresh-all-button"() {
      this.refresh();
    },
  },
  initialize({ userId }) {
    const user = new UserModel({ id: userId });

    this.views = {
      friends: new FriendshipListView({
        collection: new FriendshipCollection([], { user }),
        type: "friend"
      }),
      pending: new FriendshipListView({
        collection: new FriendshipCollection([], { user, mode: "pending" }),
        type: "pending"
      }),
      requested: new FriendshipListView({
        collection: new FriendshipCollection([], { user, mode: "requests" }),
        type: "request"
      }),
    };

    _.bindAll(this, "render", "refresh");
  },
  render() {
    this.$el.html(this.template());

    for (const [name, view] of Object.entries(this.views)) {
      view.render();

      const container = this.$(`#container-${name}`);

      container.empty();
      container.append(view.el);
    }

    return this;
  },
  refresh() {
    Object.values(this.views).forEach((view) => view.refresh());
  },
});

export default FriendshipListsView;

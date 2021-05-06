import Backbone from "backbone";
import _ from "underscore";

import UserModel from "./UserModel";

const UserProfileView = Backbone.View.extend({
  template: _.template($("script[id='template-user-profile']").html()),
  events: {},
  initialize({ id, fetch = true }) {
    this.user = new UserModel({ id });

    _.bindAll(this, "render");

    this.user.on("change", this.render);

    if (fetch) {
      this.fetch();
    }
  },
  render() {
    this.$el.html(
      this.template({
        error: this.user.get("$error"),
        loading: this.user.get("$loading"),
        isSelf: this.user.id === currentUser.id,
        user: this.user.toJSON(),
      })
    );

    this.$('[data-toggle="tooltip"]').tooltip();

    return this;
  },
  fetch() {
    if (this.user.get("$loading")) {
      return;
    }

    this.user.set("$loading", true);

    return this.user
      .fetch()
      .catch((error) => this.user.set("$error", error))
      .then(() => this.user.set("$loading", false));
  },
});

export default UserProfileView;

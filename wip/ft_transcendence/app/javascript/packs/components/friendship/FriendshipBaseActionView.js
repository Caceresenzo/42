import Backbone from "backbone";
import _ from "underscore";

import { GenericErrorView } from "../generic";

import FriendshipModel from "./FriendshipModel";
import { UserModel } from "../user";

const FriendshipBaseActionView = Backbone.View.extend({
  baseTemplate: _.template($("script[id='template-generic-action']").html()),
  initialize(options) {
    const { userId } = options;

    this.user = new UserModel({ id: userId });
    this.friendship = new FriendshipModel({ user: this.user });

    this.state = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
    });

    _.bindAll(this, "render", "fetch", "onYes");

    this.state.bind("change", this.render);
    this.user.bind("change", this.render);

    this.fetch();

    this.impl = null;
  },
  fetch() {
    this.state.set({ loading: true });

    return this.user.fetch()
      .then(() => this.state.set({ loading: false }))
      .catch((error) => this.state.set({ loading: false, error }));
  },
  render() {
    const data = {
      user: this.user.toJSON(),
      state: this.state.toJSON(),
    };

    this.$el.html(this.baseTemplate(data));

    this.$yesButton = this.$("#yes-button");
    this.$backButton = this.$("#back-button");

    this.$yesButton.on("click", this.onYes);
    this.$backButton.attr("href", `#user/${this.user.id}`);

    this.$2 = this.$("#impl-container");
    if (this.$2 && this.impl) {
      this.impl.render2(this.$2, data);

      new GenericErrorView({
        state: this.impl.state2,
        into: this.$2,
      }).render();
    }

    return this;
  },
  onYes() {
    /* no operation */
  },
  notifyImpl(instance) {
    this.impl = instance;
  },
});

export default FriendshipBaseActionView;

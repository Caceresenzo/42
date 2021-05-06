import Backbone from "backbone";
import _ from "underscore";

import FriendshipBaseActionView from "./FriendshipBaseActionView";

const FriendshipSimpleActionView = FriendshipBaseActionView.extend({
  initialize() {
    FriendshipBaseActionView.prototype.initialize.apply(this, arguments);

    this.state2 = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
    });

    _.bindAll(this, "render2");
    this.notifyImpl(this);

    this.state2.bind("change", this.render2);
  },
  render2() {
    this.$2.html(
      this.template({
        user: this.user.toJSON(),
        state: this.state2.toJSON(),
      })
    );

    return this;
  },
  onYes() {
    this.state2.set({ loading: true, error: null });

    const onSuccess = () => (window.location.hash = `#friendships`);
    const onError = () => this.state2.set({ loading: false, error });

    this.onYes2(onSuccess, onError);
  },
  onYes2(onSuccess, onError) {
    /* no operation */
  },
});

export default FriendshipSimpleActionView;

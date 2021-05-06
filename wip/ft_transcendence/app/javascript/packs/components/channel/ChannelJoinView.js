import Backbone from "backbone";
import _ from "underscore";

import ChannelBaseActionView from "./ChannelBaseActionView";

const ChannelJoinView = ChannelBaseActionView.extend({
  template: _.template($("script[id='template-channel-join']").html()),
  initialize() {
    ChannelBaseActionView.prototype.initialize.apply(this, arguments);

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
        channel: this.channel.toJSON(),
        state: this.state2.toJSON(),
      })
    );

    return this;
  },
  onYes() {
    this.state2.set({ loading: true });

    new (Backbone.Model.extend({
      urlRoot: `/api/channels/${this.channel.id}/join`,
    }))()
      .save()
      .then(() => (window.location.hash = `#channel/${this.channel.id}`))
      .catch((error) => this.state2.set({ loading: false, error }));
  },
});

export default ChannelJoinView;

import Backbone from "backbone";

import ChannelUserModel from "./ChannelUserModel";

const ChannelUserCollection = Backbone.Collection.extend({
  model: ChannelUserModel,
  initialize([], { channel }) {
    this.channel = channel;

    _.bindAll(this, "merge");

    this.merge(); /* lazy subscription */
    this.channel.on("change:members", this.merge);
  },
  url() {
    return `/api/channels/${this.channel.id}/members`;
  },
  merge() {
    this.set(this.channel.get("members") || {});
  },
});

export default ChannelUserCollection;

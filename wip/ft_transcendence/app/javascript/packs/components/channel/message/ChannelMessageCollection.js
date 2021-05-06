import Backbone from "backbone";

import ChannelMessageModel from "./ChannelMessageModel";

const ChannelMessageCollection = Backbone.Collection.extend({
  model: ChannelMessageModel,
  initialize([], { channel }) {
    this.channel = channel;
  },
  url() {
    return `/api/channels/${this.channel.id}/messages`;
  },
});

export default ChannelMessageCollection;

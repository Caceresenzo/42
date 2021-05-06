import Backbone from "backbone";

const ChannelMessageModel = Backbone.Model.extend({
  initialize({ channel }) {
    this.channel = channel;
  },
  urlRoot() {
    return `/api/channels/${this.channel.id}/messages`;
  },
});

export default ChannelMessageModel;
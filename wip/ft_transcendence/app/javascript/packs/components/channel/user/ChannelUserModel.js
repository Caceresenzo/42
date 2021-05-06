import Backbone from "backbone";

const ChannelUserModel = Backbone.Model.extend({
  initialize({ channel }) {
    this.channel = channel;
  },
  urlRoot() {
    return `/api/channels/${this.channel.id}/members`;
  },
});

export default ChannelUserModel;
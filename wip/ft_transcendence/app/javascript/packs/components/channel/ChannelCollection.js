import ChannelModel from "./ChannelModel"

const ChannelCollection = Backbone.Model.extend({
  model: ChannelModel,
  url: "/api/channels",
});

export default ChannelCollection;
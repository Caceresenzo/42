import Backbone from "backbone";
import _ from "underscore";

import FriendshipSimpleActionView from "./FriendshipSimpleActionView";

const FriendshipAcceptView = FriendshipSimpleActionView.extend({
  template: _.template($("script[id='template-friendship-accept']").html()),
  onYes(onSuccess, onError) {
    this.friendship.save().then(onSuccess).catch(onError);
  },
});

export default FriendshipAcceptView;

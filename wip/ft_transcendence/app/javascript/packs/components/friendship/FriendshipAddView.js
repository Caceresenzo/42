import Backbone from "backbone";
import _ from "underscore";

import FriendshipSimpleActionView from "./FriendshipSimpleActionView";

const FriendshipAddView = FriendshipSimpleActionView.extend({
  template: _.template($("script[id='template-friendship-add']").html()),
  onYes2(onSuccess, onError) {
    this.friendship.save().then(onSuccess).catch(onError);
  },
});

export default FriendshipAddView;

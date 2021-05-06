import Backbone from "backbone";

const UserModel = Backbone.Model.extend({
  urlRoot: "/api/users",
  default: {
    $loading: false,
    $error: null,
  },
});

export default UserModel;

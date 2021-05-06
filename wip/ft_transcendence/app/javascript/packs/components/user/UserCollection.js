import Backbone from "backbone";

import UserModel from "./UserModel";

const UserCollection = Backbone.Collection.extend({
  url: "/api/users",
  model: UserModel,
});

export default UserCollection;
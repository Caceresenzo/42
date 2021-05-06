import Backbone from "backbone";
import _ from "underscore";

const UserListView = Backbone.View.extend({
  template: _.template($("script[id='template-user-list']").html()),
  initialize({ collection, fetch }) {
    this.collection = collection;

    _.bindAll(this, "render");

    this.collection.bind("reset", this.render);
    this.collection.bind("add", this.render);
    this.collection.bind("change", this.render);
    this.collection.bind("remove", this.render);

    if (fetch) {
      this.collection.fetch();
    }
  },
  render() {
    this.$el.html(
      this.template({
        users: this.collection.toJSON(),
      })
    );

    return this;
  },
});

export default UserListView;

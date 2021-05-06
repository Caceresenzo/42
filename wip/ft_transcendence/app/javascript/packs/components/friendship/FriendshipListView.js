import Backbone from "backbone";
import _ from "underscore";

const FriendshipBasicView = Backbone.View.extend({
  initialize({ model }) {
    this.model = model;

    _.bindAll(this, "render");

    this.model.on("change", this.render);
  },
  render() {
    this.$el.html(
      this.template({
        friendship: this.model.toJSON(),
      })
    );

    return this;
  },
});

const FriendshipItemFriendView = FriendshipBasicView.extend({
  template: _.template($("script[id='template-friendship-friend']").html()),
});

const FriendshipItemPendingView = FriendshipBasicView.extend({
  template: _.template($("script[id='template-friendship-pending']").html()),
});

const FriendshipItemRequestView = FriendshipBasicView.extend({
  template: _.template($("script[id='template-friendship-request']").html()),
});

const ITEM_VIEW_TYPES = {
  friend: FriendshipItemFriendView,
  pending: FriendshipItemPendingView,
  request: FriendshipItemRequestView,
}

const FriendshipListView = Backbone.View.extend({
  template: _.template($("script[id='template-friendship-list']").html()),
  events: {
    "click .refresh-button"() {
      this.refresh();
    },
  },
  initialize({ collection, type, fetch = true }) {
    this.collection = collection;
    this.viewImpl = ITEM_VIEW_TYPES[type];

    this.state = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
    });

    _.bindAll(this, "render", "refresh", "addOne");

    this.collection.bind("reset", this.render);
    this.collection.bind("add", this.addOne);
    this.collection.bind("change", this.render);
    this.collection.bind("remove", this.render);

    this.state.bind("change", this.render);

    if (fetch) {
      this.refresh();
    }
  },
  render() {
    this.$el.html(
      this.template({
        state: this.state.toJSON(),
        friendships: this.collection.toJSON(),
      })
    );

    this.$list = this.$(".friendship-list")
    this.addAll()

    return this;
  },
  addAll() {
    this.collection.each(this.addOne);
  },
  addOne(model) {
    this.$list.append(
      new this.viewImpl({
        model,
      }).render().el
    );
  },
  refresh() {
    if (this.state.get("loading")) {
      return;
    }

    this.state.set({ loading: true, error: null });

    return this.collection
      .fetch()
      .then(() => this.state.set({ loading: false }))
      .catch((error) => this.state.set({ error, loading: false }));
  },
});

export default FriendshipListView;

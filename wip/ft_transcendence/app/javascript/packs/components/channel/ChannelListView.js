import Backbone from "backbone";
import _ from "underscore";

const ChannelListView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-list']").html()),
  events: {
    "click #refresh-button"() {
      this.refresh();
    },
  },
  initialize({ collection, fetch = true }) {
    this.collection = collection;

    this.state = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
    });

    _.bindAll(this, "render", "refresh");

    this.collection.bind("reset", this.render);
    this.collection.bind("add", this.render);
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
        channels: this.collection.toJSON(),
      })
    );

    return this;
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

export default ChannelListView;

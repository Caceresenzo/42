const EmptyView = Backbone.View.extend({
  template: _.template($("script[id='template-empty']").html()),
  render() {
    this.$el.html(this.template());

    return this;
  },
});

const SimpleView = Backbone.View.extend({
  initialize({ template, data }) {
    this.template = _.template($(template).html());
    this.data = data;
  },
  render() {
    this.$el.html(this.template(this.data));

    return this;
  },
});

export { EmptyView, SimpleView };

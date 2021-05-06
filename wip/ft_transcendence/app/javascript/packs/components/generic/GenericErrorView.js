import Backbone from "backbone";
import _ from "underscore";

const GenericErrorView = Backbone.View.extend({
  template: _.template(
    $("script[id='template-generic-action-error']").html()
  ),
  initialize({ state, into }) {
    this.state = state;
    this.into = into;

    _.bindAll(this, "render");

    this.state.bind("change", this.render);
  },
  render() {
    const el = this.into.find("#error-container");

    if (el) {
      el.empty();
      el.html(this.template(this.state.toJSON()));
    }

    return this;
  },
});

export default GenericErrorView;
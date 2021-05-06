import "@mdi/font/css/materialdesignicons";

require("@rails/ujs").start();
require("@rails/activestorage").start();
require("channels");
require("jquery-ui");
require("bootstrap");

window._ = require("underscore");
window.$ = window.jQuery = require("jquery");
window.Backbone = require("backbone");

require("./libs/jquery_extra");
require("./libs/underscore_extra");
require("./libs/backbone_extra");

const Router = require("./router");
const NavigationBar = require("./components/navigation_bar");

var AppView = Backbone.View.extend({
  el: "#app",
  initialize() {
    this.model = new (Backbone.Model.extend({
      default: {
        view: null,
      },
    }))();

    this.model.on("change:view", this.render, this);
  },
  render() {
    let view = this.model.get("view");

    if (view) {
      this.$el.html(view.render().el);
    } else {
      this.$el.html();
    }
  },
  set(view) {
    this.model.get("view")?.close();
    this.model.set("view", view);
  },
});

const app = {
  setView(view) {
    this.view.set(view);
  },
  start() {
    this.navigationBarView = new NavigationBar.NavigationBarView();

    this.view = new AppView();

    /* the Router.default is a hack... */
    this.router = new Router.default({ app: this });

    this.navigationBarView.render();
    this.view.render();

    Backbone.history.start();
  },
};

export default app;

const bsCustomFileInput = require("bs-custom-file-input");
require("jquery-qrcode2");
$(document).ready(function () {
  bsCustomFileInput.init();
});

$(document).ready(function () {
  app.start();
});
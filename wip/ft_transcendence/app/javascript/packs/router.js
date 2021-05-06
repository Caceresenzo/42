import Backbone from "backbone";

import Routes from "./routes";

const Router = Backbone.Router.extend({
  routes: {
    /* will be generated */
  },
  constructor() {
    this.generateRoutes();

    Backbone.Router.apply(this, arguments);

    return this;
  },
  initialize({ app }) {
    this.app = app;
  },
  setActive(route) {
    this.app.navigationBarView.setActive(route);
  },
  generateRoutes() {
    for (const [route, options] of Object.entries(Routes)) {
      const { group, view } = options;

      this.routes[route.substring(1)] = function () {
        this.setActive(group);

        this.app.setView(view.apply(this, arguments));
      };
    }
  },
});

export default Router;

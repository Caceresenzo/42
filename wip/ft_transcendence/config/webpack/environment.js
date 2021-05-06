const { environment } = require("@rails/webpacker");
const webpack = require("webpack");

environment.plugins.prepend(
  "Provide",
  new webpack.ProvidePlugin({
    $: "jquery",
    _: "underscore",
    jQuery: "jquery",
    jquery: "jquery",
    underscore: "underscore",
    "window.jQuery": "jquery",
    "window.underscore": "underscore",
    Popper: ["popper.js", "default"],
  })
);

/* garbage: https://ryanfb.github.io/etc/2020/09/24/webpacker_and_rails_with_jquery_global_object.html */
environment.loaders.append("jquery", {
  test: require.resolve("jquery"),
  loader: "expose-loader",
  options: {
    exposes: ["$", "jQuery"],
  },
});

//environment.splitChunks();

/*environment.plugins.prepend(
    "Provide",
    new webpack.ProvidePlugin({
        $: "jquery",
        _: "underscore",
        jQuery: "jquery",
        jquery: "jquery",
        underscore: "underscore",
        "window.jQuery": "jquery",
        "window.underscore": "underscore",
        Popper: ["popper.js", "default"],
    })
);*/

module.exports = environment;

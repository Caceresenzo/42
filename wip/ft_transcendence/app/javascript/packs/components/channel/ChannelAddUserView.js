import Backbone from "backbone";
import _ from "underscore";

import ChannelBaseActionView from "./ChannelBaseActionView";

const ChannelAddUserView = ChannelBaseActionView.extend({
  template: _.template($("script[id='template-channel-add']").html()),
  initialize() {
    ChannelBaseActionView.prototype.initialize.apply(this, arguments);

    this.state2 = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
      success: false,
    });

    _.bindAll(this, "render2");
    this.notifyImpl(this);

    this.state2.bind("change", this.render2);
  },
  render2() {
    this.$2.html(
      this.template({
        channel: this.channel.toJSON(),
        user: this.user.toJSON(),
        state: this.state2.toJSON(),
      })
    );

    this.$usernameSelect = this.$("#username-select").select2({
      ajax: {
        url: "/api/search/users",
        data: (params) => ({ query: params.term }),
        dataType: "json",
        processResults: (data) => ({
          results: _.map(data.users, (x) => {
            x.text = x.username;
            return x;
          }),
        }),
      },
      placeholder: "search a user",
      minimumInputLength: 1,
    });

    return this;
  },
  onYes() {
    const selected = this.$usernameSelect.val();

    if (selected) {
      this.state2.set({ loading: true });

      this.user
        .save({
          user_id: selected,
        })
        .then(() => (window.location.hash = `#channel/${this.channel.id}`))
        .catch((error) => this.state2.set({ loading: false, error }));
    }
  },
});

export default ChannelAddUserView;

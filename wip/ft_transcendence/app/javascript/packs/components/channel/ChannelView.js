import Backbone from "backbone";
import _ from "underscore";
import consumer from "../../../channels/consumer";

import ValidationHelper from "../../helper/validation";

import ChannelModel from "./ChannelModel";

import { ChannelMessageModel, ChannelMessageCollection } from "./message";
import { ChannelUserModel, ChannelUserCollection } from "./user";

const LoadingView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-loading']").html()),
  render() {
    this.$el.html(this.template());

    return this;
  },
});

const ErrorView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-error']").html()),
  initialize({ status, message, refresh }) {
    this.status = status;
    this.message = message;
    this.refresh = refresh;

    _.bindAll(this, "render");
  },
  events: {
    "click #refresh"() {
      this.refresh();
    },
  },
  render() {
    this.$el.html(
      this.template({
        status: this.status,
        message: this.message,
      })
    );

    return this;
  },
});

const PasswordProtectedView = Backbone.View.extend({
  template: _.template(
    $("script[id='template-channel-password-protected']").html()
  ),
  initialize({ channel, refresh }) {
    this.channel = channel;
    this.refresh = refresh;

    _.bindAll(this, "render");
  },
  render() {
    this.$el.html(
      this.template({
        channel: this.channel.toJSON(),
      })
    );

    return this;
  },
  events: {
    "click #refresh"() {
      this.refresh();
    },
  },
});

const PrivateView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-private']").html()),
  initialize({ channel, refresh }) {
    this.channel = channel;
    this.refresh = refresh;

    _.bindAll(this, "render");
  },
  render() {
    this.$el.html(this.template());

    return this;
  },
  events: {
    "click #refresh"() {
      this.refresh();
    },
  },
});

const MessageView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-message']").html()),
  initialize({ model }) {
    this.model = model;

    _.bindAll(this, "render");

    this.model.on("change", this.render);
  },
  render() {
    this.$el.html(this.template(this.model.toJSON()));

    return this;
  },
  events: {
    "click .channel-message"() {
      console.log("TODO: Display profile in modal");
    },
  },
});

const MessageInputView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-message-input']").html()),
  validationSelectors: {
    form: "",
    fields: {
      content: "#message-invalid",
    },
  },
  initialize({ channel, collection }) {
    this.channel = channel;
    this.collection = collection;

    this.state = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
    });

    _.bindAll(
      this,
      "$",
      "render",
      "submit",
      "updateLoadingState",
      "updateErrorState",
      "setInputEnabledState"
    );

    this.state.bind("change:loading", this.updateLoadingState);
    this.state.bind("change:error", this.updateErrorState);
  },
  render() {
    this.$el.html(this.template());

    this.$messageInput = this.$("#message-input");
    this.$loadingContainer = this.$("#loading-container");

    this.updateLoadingState();

    return this;
  },
  submit() {
    if (this.state.get("loading")) {
      return;
    }

    const message = this.$messageInput.val();

    if (!message) {
      return;
    }

    this.state.set({
      loading: true,
      error: null,
    });

    this.setInputEnabledState();

    new ChannelMessageModel({
      channel: this.channel,
    })
      .save({
        content_type: "text",
        content: message,
      })
      .then(() => {
        this.$messageInput.val("");
        this.state.set({
          loading: false,
        });
      })
      .catch((error) => {
        this.state.set({
          error,
          loading: false,
        });
      })
      .then(this.setInputEnabledState);
  },
  setInputEnabledState() {
    const loading = this.state.get("loading");

    if (loading) {
      this.$messageInput.disable();
    } else {
      this.$messageInput.enable();
      this.$messageInput.focus();
    }
  },
  updateLoadingState() {
    const loading = this.state.get("loading");

    if (loading) {
      this.$loadingContainer.show();
    } else {
      this.$loadingContainer.hide();
    }
  },
  updateErrorState() {
    const error = this.state.get("error");

    if (error) {
      if (error.status == 406) {
        const fields = error.responseJSON.fields;

        ValidationHelper.failed(this.$, fields, this.validationSelectors);
      } else {
        const selector = this.validationSelectors.fields.content;

        this.$(selector).show();
        this.$(selector).text(
          error.responseJSON?.message ||
            error.status ||
            "failed to send the message"
        );
      }
    } else {
      ValidationHelper.clear(this.$, this.validationSelectors);
    }
  },
  events: {
    "click #send-button"() {
      this.submit();
    },
    "keyup #message-input"(event) {
      if (event.keyCode == 13 /* enter */) {
        this.submit();
      }
    },
  },
});

const MessageInputViewMustJoin = Backbone.View.extend({
  template: _.template(
    $("script[id='template-channel-message-input-must-join']").html()
  ),
  initialize({ channel }) {
    this.channel = channel;
  },
  render() {
    this.$el.html(
      this.template({
        channel: this.channel.toJSON(),
      })
    );

    return this;
  },
});

const MessageListView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-message-list']").html()),
  initialize({ collection, channel }) {
    this.collection = collection;
    this.channel = channel;

    _.bindAll(this, "render", "addOne", "addOneAndScroll");

    this.collection.bind("reset", this.render);
    this.collection.bind("add", this.addOneAndScroll);
    this.collection.bind("change", this.render);
    this.collection.bind("remove", this.render);
  },
  render() {
    this.$el.html(this.template());

    this.$container = this.$("#message-container");
    this.$inputContainer = this.$("#message-input-container");

    if (this.channel.isMember(currentUser)) {
      this.$inputContainer.append(
        new MessageInputView({
          channel: this.channel,
          collection: this.collection,
        }).render().el
      );
    } else {
      this.$inputContainer.append(
        new MessageInputViewMustJoin({
          channel: this.channel,
        }).render().el
      );
    }

    this.addAll();

    return this;
  },
  addOneAndScroll(model) {
    this.addOne(model);
    this.scrollToBottom();
  },
  addAll() {
    this.collection.each(this.addOne);
    this.scrollToBottom();
  },
  addOne(model) {
    this.$container.append(
      new MessageView({
        model,
      }).render().$el
    );
  },
  scrollToBottom() {
    const div = this.$container;

    if (div[0]) {
      div.scrollTop(div[0].scrollHeight);
    }
  },
});

const MemberView = Backbone.View.extend({
  template: _.template($("script[id='template-channel-member']").html()),
  initialize({ channel, model }) {
    this.channel = channel;
    this.model = model;

    _.bindAll(this, "render");

    this.model.on("change", this.render);
  },
  render() {
    this.$el.html(
      this.template({
        member: this.model.toJSON(),
        channel: this.channel.toJSON(),
        isOwner: this.channel.isOwner(currentUser),
        isAdmin: this.channel.isAdmin(currentUser),
      })
    );

    return this;
  },
  events: {
    "click .channel-member"() {
      console.log("TODO: Display profile in modal");
    },
  },
});

const MemberListView = Backbone.View.extend({
  initialize({ channel, collection }) {
    this.channel = channel;
    this.collection = collection;

    _.bindAll(this, "render", "addOne");

    this.collection.bind("reset", this.render);
    this.collection.bind("add", this.addOne);
    this.collection.bind("change", this.render);
    this.collection.bind("remove", this.render);
  },
  render() {
    this.$el.empty();
    this.addAll();

    return this;
  },
  addAll() {
    this.collection.each(this.addOne);
  },
  addOne(model) {
    this.$el.append(
      new MemberView({
        channel: this.channel,
        model,
      }).render().el
    );
  },
});

const ChannelView = Backbone.View.extend({
  template: _.template($("script[id='template-channel']").html()),
  events: {
    "click #error-refresh": "refresh",
    "click #refresh-action": "refresh",
  },
  initialize({ id }) {
    this.channel = new ChannelModel({ id });
    this.members = new ChannelUserCollection([], { channel: this.channel });
    this.messages = new ChannelMessageCollection([], { channel: this.channel });

    this.state = new (Backbone.Model.extend({}))({
      loading: false,
      error: null,
      connected: false,
      rejected: false,
    });

    _.bindAll(this, "render", "connect", "refresh");

    this.state.on("change", this.render);
    this.channel.on("change", this.render);

    this.refresh();
  },
  render() {
    this.$el.empty();

    if (this.state.get("loading")) {
      this.$el.append(new LoadingView().render().$el);
    } else if (this.state.get("error")) {
      const error = this.state.get("error");
      const message = error.responseJSON?.message;

      if (message === "password protected") {
        this.$el.append(
          new PasswordProtectedView({
            channel: this.channel,
            refresh: this.refresh,
          }).render().$el
        );
      } else if (message === "private") {
        this.$el.append(
          new PrivateView({
            channel: this.channel,
            refresh: this.refresh,
          }).render().$el
        );
      } else {
        this.$el.append(
          new ErrorView({
            status: error.status,
            message: error.responseJSON?.message,
            refresh: this.refresh,
          }).render().$el
        );
      }
    } else {
      this.$el.html(
        this.template({
          state: this.state.toJSON(),
          channel: this.channel.toJSON(),
          isOwner: this.channel.isOwner(currentUser),
          isAdmin: this.channel.isAdmin(currentUser),
          isMember: this.channel.isMember(currentUser),
        })
      );

      new MessageListView({
        el: this.$("#messages-part"),
        channel: this.channel,
        collection: this.messages,
      }).render();

      new MemberListView({
        el: this.$("#members-part"),
        channel: this.channel,
        collection: this.members,
      }).render();

      this.$messageContainer = this.$("#message-container");
    }

    return this;
  },
  fetch() {
    if (this.state.get("loading")) {
      return;
    }

    this.state.set({ loading: true });

    return this.channel
      .fetch()
      .then(() => this.messages.fetch())
      .catch((error) => this.state.set({ error }))
      .then(() => this.state.set({ loading: false }));
  },
  refresh() {
    this.state.set({ error: null, rejected: false, connected: false });

    this.disconnect();
    this.subscriber = null;

    this.fetch().then(this.connect);
  },
  connect() {
    if (this.state.get("error")) {
      return;
    }

    this.subscriber = consumer.subscriptions.create(
      {
        channel: "ChannelChannel",
        channel_id: this.channel.id,
      },
      {
        connected: (x) => {
          console.log("connected(): " + x);
          this.state.set("connected", true);
        },
        rejected: (x) => {
          this.state.set("rejected", true);
          console.log("rejected(): " + x);
        },
        disconnected: (x) => {
          console.log("disconnected(): " + x);
          this.state.set("connected", false);
        },
        received: (data) => {
          console.log("received(" + JSON.stringify(data) + ")");

          const { event, item } = data;

          switch (event) {
            case "message": {
              this.messages.add(item);
              break;
            }

            case "member.update": {
              this.members
                .where((x) => x.get("user").id == item.user.id, true)
                ?.set(item);
              break;
            }

            case "member.join": {
              this.members.add([new ChannelUserModel(item)]);
              break;
            }

            case "member.leave": {
              this.members.remove(
                this.members.where((x) => x.get("user").id == item.user.id)
              );
              break;
            }

            case "clear": {
              this.messages.reset();
              break;
            }

            case "delete": {
              this.refresh();
              break;
            }

			// TODO Implement transfer ownership update
          }

          if (event.startsWith("member") && item.user.id == currentUser.id) {
            this.refresh();
          }
        },
      }
    );
  },
  disconnect() {
    if (this.subscriber) {
      consumer.subscriptions.remove(this.subscriber);
    }
  },
  onClose() {
    this.disconnect();
  },
});

export default ChannelView;

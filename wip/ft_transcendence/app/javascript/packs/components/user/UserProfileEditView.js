import Backbone from "backbone";
import _ from "underscore";

import ValidationHelper from "../../helper/validation";

const UserSettingsModel = Backbone.Model.extend({
  url: "/api/users/current/settings",
  default: {
    otp: false,
    username: null,
  },
});

const UserProfileEditView = Backbone.View.extend({
  template: _.template($("script[id='template-user-profile-edit']").html()),
  events: {
    "click #submit-button": "submit",
    "click #upload-button": "upload",
    "change #file-input": "changeInput",
    "click #refresh-button"() {
      console.log("qsd");
      this.refresh();
    },
    "click #qrcode-button"() {
      this.$otpQrcodeModal.modal("show");
    },
  },
  validationSelectors: {
    form: "",
    fields: {
      username: "#username-invalid",
    },
  },
  initialize(options) {
    this.settings = new UserSettingsModel();
    this.state = new (Backbone.Model.extend())({
      loading: false,
      error: null,
      error2: null,
    });

    _.bindAll(this, "$", "render", "submit", "refresh");

    this.settings.bind("change", this.render);
    this.state.bind("change", this.render);

    this.refresh();
  },
  render() {
    this.$el.html(
      this.template({
        state: this.state.toJSON(),
      })
    );

    this.$usernameInput = this.$("#username-input");
    this.$twoFactorEnabledCheckbox = this.$("#two-factor-enabled-checkbox");

    this.$previewImage = this.$("#preview-image");
    this.$fileInput = this.$("#file-input");

    this.$otpQrcodeModal = this.$("#otp-qrcode-modal");

    if (this.settings.get("username")) {
      this.$usernameInput.val(this.settings.get("username"));
      this.$twoFactorEnabledCheckbox.prop("checked", this.settings.get("otp"));
      this.$previewImage.attr("src", this.settings.get("picture"));

      this.$("#qrcode").qrcode({
        text: this.settings.get("otp_url"),
        quiet: 1,
        size: 400,
      });
    }

    return this;
  },
  upload() {
    console.log("TODO @badria");
  },
  refresh() {
    if (this.state.get("loading")) {
      return;
    }

    this.state.set({ loading: true, error: null, error2: null });

    this.settings
      .fetch()
      .then(() => this.state.set({ loading: false }))
      .catch((error) => this.state.set({ loading: false, error }));
  },
  submit() {
    if (this.state.get("loading")) {
      return;
    }

    const props = {
      username: this.$usernameInput.val(),
      otp: this.$twoFactorEnabledCheckbox.prop("checked"),
    };

    this.state.set({ loading: true, error: null, error2: null });

    this.settings
      .save(props)
      .then(() => this.state.set({ loading: false }))
      .catch((error) => {
        this.state.set({ loading: false, error2: error });

        if (error.status == 406) {
          const fields = error.responseJSON.fields;

          ValidationHelper.failed(this.$, fields, this.validationSelectors);
        }
      });
  },
  changeInput(event) {
    var input = this.$fileInput[0];

    if (input.files && input.files[0]) {
      var reader = new FileReader();
      reader.onload = (e) => {
        this.$previewImage.attr("src", e.target.result).fadeIn("slow");
      };
      reader.readAsDataURL(input.files[0]);
    }
  },
  onClose() {
    this.$otpQrcodeModal.modal("hide");
  },
});

export default UserProfileEditView;

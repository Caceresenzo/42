import Backbone from "backbone";

/* from: https://coderwall.com/p/xj81ua/a-better-way-of-extending-backbone-models-and-views */

(function (Model) {
  "use strict";
  // Additional extension layer for Models
  Model.fullExtend = function (protoProps, staticProps) {
    // Call default extend method
    var extended = Model.extend.call(this, protoProps, staticProps);
    // Add a usable super method for better inheritance
    extended.prototype._super = this.prototype;
    // Apply new or different defaults on top of the original
    if (protoProps.defaults) {
      for (var k in this.prototype.defaults) {
        if (!extended.prototype.defaults[k]) {
          extended.prototype.defaults[k] = this.prototype.defaults[k];
        }
      }
    }
    return extended;
  };
})(Backbone.Model);

Backbone.View.fullExtend = function (protoProps, staticProps) {
  const extended = Backbone.View.extend.call(this, protoProps, staticProps);
  extended.prototype._super = this.prototype;

  if (protoProps.events) {
    for (const k in this.prototype.events) {
      if (!extended.prototype.events[k]) {
        extended.prototype.events[k] = this.prototype.events[k];
      }
    }
  }
  return extended;
};

Backbone.View.prototype.close = function () {
  if (this.onClose) {
    this.onClose();
  }
  this.remove();
  this.unbind();
  if (this.afterClose) {
    this.afterClose();
  }
};

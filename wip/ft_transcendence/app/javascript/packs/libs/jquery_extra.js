import jquery from "jquery";
import 'select2';
import 'select2/dist/css/select2.css';

jquery.fn.extend({
  disable() {
    return this.prop("disabled", true);
  },
  enable() {
    return this.removeAttr("disabled");
  },
});

export default class ValidationHelper {
  static failed($$, errors, selectors) {
    const { form, fields } = selectors;

    ValidationHelper.clear($$, selectors);

    for (const field in errors) {
      const validations = errors[field];
      const selector = fields[field];

      $$(selector).show();
      $$(selector).text(validations.join(", "));
    }
  }
  static clear($$, selectors) {
    const { form, fields } = selectors;

    for (const selector of Object.values(fields)) {
      $$(selector).text("");
      $$(selector).hide();
    }
  }
}

import Vue from 'vue'

export interface FieldValidationError {
  message: string
  path: string
}
export interface SegmentValidationError {
  fields: Array<FieldValidationError>
}

export interface ValidationError {
  body: SegmentValidationError
}

export default class JoiHelper {
  static extract(error: ValidationError, into: any) {
    for (const key of Object.keys(into)) {
      Vue.delete(into, key)
    }

    for (const field of error.body.fields) {
      Vue.set(into, field.path, field.message)
    }
  }
}

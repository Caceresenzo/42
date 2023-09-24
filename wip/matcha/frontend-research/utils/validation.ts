export function extractValidation(error: any): { [key: string]: Array<string> } {
    const violations = error?.response?.data?.violations || []
    const validations = {} as { [key: string]: Array<string> }

    for (const { message, propertyPath } of violations) {
        if (!(propertyPath in validations)) {
            validations[propertyPath as string] = [message]
        } else {
            validations[propertyPath as string].push(message)
        }
    }

    return validations
}
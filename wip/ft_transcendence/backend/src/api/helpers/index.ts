export default {
  notFound(message) {
    const error = new Error(message);
    error["status"] = 404;
    throw error;
  },
  conflict(message) {
    const error = new Error(message);
    error["status"] = 409;
    throw error;
  },
  forbidden(message) {
    const error = new Error(message);
    error["status"] = 403;
    throw error;
  },
  bad(message) {
    const error = new Error(message);
    error["status"] = 400;
    throw error;
  },
};

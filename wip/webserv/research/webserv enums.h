
#define ENUM_DEFINE(clazz, name, constructor) clazz *clazz::name = clazz::enumValue(#name, constructor);
#define DEFINE_METHOD(name, handler) ENUM_DEFINE(HTTPMethod, name, HTTPMethod(handler));

DEFINE_METHOD(GET,/*     */new GetHandler());

HTTPMethod *HTTPMethod::GET = HTTPMethod::enumValue("GET", HTTPMethod(new GetHandler()));
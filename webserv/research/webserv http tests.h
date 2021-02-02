void test(const char *str, HTTPMethod *method, const std::string &path, HTTPVersion *version, const HTTPHeaderFields &fields)
{
	HTTPRequestParser parser;
	
	while (*str && parser.consume(*str) && parser.status() != HTTPRequestParser:S_END)
		str++;
		
	if (parser.method() != method->name())
		throw Exception("Mismatch, expected method: " + method->name() + " but got " + parser.method());
		
	if (parser.path() != path)
		throw Exception("Mismatch, expected path: " + path + " but got " + parser.path());
}

main{
	
	test("GET / HTTP/1.1\r\n"
		 "Hello: World\r\n"
		 "\r\n",
		 HTTPMethod::GET,
		 "/",
		 HTTPVersion::HHTP_1_1,
		 HTTPHeaderFields().set("Hello", "World"));
	
	test("GET / HTTP/1.1\r\n"
		 "Hello: World\r\n"
		 "\r\n",
		 HTTPMethod::GET,
		 "/",
		 HTTPVersion::HHTP_1_1,
		 HTTPHeaderFields().set("Hello", "World"));
	
	test("GET / HTTP/1.1\r\n"
		 "Hello: World\r\n"
		 "\r\n",
		 HTTPMethod::GET,
		 "/",
		 HTTPVersion::HHTP_1_1,
		 HTTPHeaderFields().set("Hello", "World"));
	
}
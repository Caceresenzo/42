
JsonObject
{
	"key": ...
}

JsonArray
[
	...,
	...
]

JsonNumber
1

JsonDecimal
1.2

JsonBoolean
true

JsonBoolean
false

JsonNull
null

x = JsonReader::fromFile("xx").read()
x = JsonObject, JsonArray, ...

if (!x.instanceOf<JsonObject>())
	throw Exception("Expected JSON Object, but got: " + x.typeString());
	
JsonObject *root = x.cast<JsonObject>();

if (root->has("servers"))
{
	JsonValue *serversJsonValue = root.get("servers");

	if (!serversJsonValue.instanceOf<JsonArray>())
		throw Exception("Servers list is not an array");
		
	JsonArray *servers = serversJsonValue->cast<JsonArray>();
	
	JsonArray::iterator it = servers->begin();
	JsonArray::iterator ite = servers->end();
	
	while (it != ite)
	{
		ServerBlock serverBlock;
		
		if (!it->instanceOf<JsonObject>())
			throw Exception("Server is not an object");
		
		JsonObject *server = it->cast<JsonObject>();
		
		if (server->has("port"))
		{
			JsonValue *portValue = server.get("port");
			
			if (!portValue->instanceOf<JsonNumber>())
				throw Exception("Server port is not a number");
			
			serverBlock.port(portValue->cast<JsonNumber>());
		}
		
		if (server->has("host"))
		{
			JsonValue *hostValue = server.get("host");
			
			if (!portValue->instanceOf<JsonString>())
				throw Exception("Server host is not a string");
			
			serverBlock.host(portValue->cast<JsonString>());
		}
		
		if (server->has("name"))
		{
			JsonValue *jsonValue = server.get("name");
			
			if (jsonValue->instanceOf<JsonString>())
			{
				serverBlock.names(ContainerBuilder<std::string>()
					.add(jsonValue->cast<JsonString>())
					.build());
			}
			else if (jsonValue->instanceOf<JsonArray>())
			{
				JsonArray *names = jsonValue->cast<JsonArray>();
				
				JsonArray::iterator it = names.begin();
				JsonArray::iterator ite = names.end();
				
				std::vector<std::string> serverNames;
				
				while (it != ite)
				{
					if (!it->instanceOf<JsonString>())
						throw Exception("Server name is not a string value (in array)");
					
					serverNames.push_back(it->cast<JsonString>());
					
					it++;
				}
				
				if (serverNames.empty())
					throw Exception("Server name array provided, but empty");
				
				serverBlock.names(serverNames);
			}
				
			
			if (!jsonValue->instanceOf<JsonString>())
				throw Exception("Server host is not a string");
			
			serverBlock.host(portValue->cast<JsonString>());
		}
		
		BIND("port", JsonNumber, int, {
			serverBlock.port(value);
		});
		
		BIND("host", JsonString, std::string, {
			serverBlock.host(value);
		});
		
		// other keys
		
		if (!serverBlock.port().present())
			throw Exception("No name has been specified for server");
			
		
		it++;
	}
}

#define BIND(key, jsonType, type, apply)											\
		if (server->has(key))														\
		{																			\
			JsonValue *jsonValue = server.get(key);									\
																					\
			if (!jsonValue->instanceOf<jsonType>())									\
				throw Exception("Server " key " is not a " #type);					\
																					\
			type value = jsonValue->cast<jsonType>();								\
																					\
			do {																	\
				apply;																\
			} while (0);															\
		}
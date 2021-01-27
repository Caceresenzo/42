# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atetu <atetu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 15:11:33 by ecaceres          #+#    #+#              #
#    Updated: 2021/01/25 16:30:07 by atetu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT			= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

COLOR_RESET				= \033[0m
COLOR_LIGHT_GREEN		= \033[92m
COLOR_LIGHT_YELLOW		= \033[93m
COLOR_LIGHT_MAGENTA		= \033[95m
COLOR_WHITE				= \033[97m

FIX_SOURCE_EXT			= cpp
FIX_HEADER_EXT			= h
FIX_GO_DEEPER			= true
FIX_SOURCES_DIR			= .
FIX_HEADERS_DIR			= .
FIX_LIBRARIES_DIR		= .

TARGET					= webserv
SOURCES					= ./base64/Base64.cpp ./buffer/IBuffer.cpp ./buffer/impl/BaseBuffer.cpp ./buffer/impl/FileDescriptorBuffer.cpp ./buffer/impl/SocketBuffer.cpp ./buffer/IReadableBuffer.cpp ./buffer/IWritableBuffer.cpp ./config/block/auth/BasicAuthBlock.cpp ./config/block/auth/BearerAuthBlock.cpp ./config/block/AuthBlock.cpp ./config/block/CGIBlock.cpp ./config/block/container/CustomErrorMap.cpp ./config/block/LocationBlock.cpp ./config/block/MimeBlock.cpp ./config/block/RootBlock.cpp ./config/block/ServerBlock.cpp ./config/Configuration.cpp ./config/exceptions/ConfigurationBindException.cpp ./config/exceptions/ConfigurationException.cpp ./config/exceptions/ConfigurationValidateException.cpp ./exception/Exception.cpp ./exception/IllegalArgumentException.cpp ./exception/IllegalStateException.cpp ./exception/IOException.cpp ./exception/NoSuchElementException.cpp ./exception/NullPointerException.cpp ./exception/RuntimeException.cpp ./http/body/encoding/chunked/ChunkDecoder.cpp ./http/body/encoding/chunked/ChunkEncoder.cpp ./http/body/encoding/exception/HTTPBodyEncodingException.cpp ./http/body/encoding/HTTPBodyEncoding.cpp ./http/body/encoding/identity/IdentityDecoder.cpp ./http/body/encoding/identity/IdentityEncoder.cpp ./http/body/encoding/IHTTPBodyDecoder.cpp ./http/body/encoding/IHTTPBodyEncoder.cpp ./http/cgi/CommonGatewayInterface.cpp ./http/cgi/task/CGITask.cpp ./http/enums/HTTPMethod.cpp ./http/enums/HTTPStatus.cpp ./http/enums/HTTPVersion.cpp ./http/filter/Filter.cpp ./http/filter/FilterChain.cpp ./http/filter/impl/after/ErrorFilter.cpp ./http/filter/impl/after/FinalFilter.cpp ./http/filter/impl/after/HeadFilter.cpp ./http/filter/impl/before/AuthenticationFilter.cpp ./http/filter/impl/before/IndexFilter.cpp ./http/filter/impl/before/LocationFilter.cpp ./http/filter/impl/before/MethodFilter.cpp ./http/filter/impl/before/ServerFilter.cpp ./http/filter/impl/between/CGIFilter.cpp ./http/filter/impl/between/MethodHandlingFilter.cpp ./http/handler/HTTPMethodHandler.cpp ./http/handler/methods/ConnectHandler.cpp ./http/handler/methods/DeleteHandler.cpp ./http/handler/methods/GetHandler.cpp ./http/handler/methods/OptionsHandler.cpp ./http/handler/methods/PostHandler.cpp ./http/handler/methods/PutHandler.cpp ./http/handler/methods/task/PutTask.cpp ./http/handler/methods/TraceHandler.cpp ./http/header/HTTPDate.cpp ./http/header/HTTPHeaderFields.cpp ./http/HTTP.cpp ./http/HTTPClient.cpp ./http/HTTPOrchestrator.cpp ./http/HTTPServer.cpp ./http/mime/MIME.cpp ./http/mime/MimeRegistry.cpp ./http/page/DefaultPages.cpp ./http/parser/exception/HTTPRequestException.cpp ./http/parser/exception/status/HTTPRequestHeaderTooBigException.cpp ./http/parser/exception/status/HTTPRequestPayloadTooLargeException.cpp ./http/parser/exception/status/HTTPRequestURLTooLongException.cpp ./http/parser/exception/version/UnsupportedHTTPVersion.cpp ./http/parser/HTTPHeaderFieldsParser.cpp ./http/parser/HTTPRequestParser.cpp ./http/parser/HTTPRequestPathParser.cpp ./http/request/HTTPRequest.cpp ./http/response/body/impl/CGIResponseBody.cpp ./http/response/body/impl/FileResponseBody.cpp ./http/response/body/impl/StringResponseBody.cpp ./http/response/body/IResponseBody.cpp ./http/response/HTTPResponse.cpp ./http/response/HTTPStatusLine.cpp ./http/route/HTTPFindLocation.cpp ./http/route/HTTPLocationInterpretor.cpp ./http/task/HTTPTask.cpp ./io/File.cpp ./io/FileDescriptor.cpp ./io/Socket.cpp ./json/JsonArray.cpp ./json/JsonBoolean.cpp ./json/JsonDecimal.cpp ./json/JsonEnumValues.cpp ./json/JsonException.cpp ./json/JsonLocation.cpp ./json/JsonNull.cpp ./json/JsonNumber.cpp ./json/JsonObject.cpp ./json/JsonParseException.cpp ./json/JsonParser.cpp ./json/JsonReader.cpp ./json/JsonString.cpp ./json/JsonStructure.cpp ./json/JsonTokenizer.cpp ./json/JsonTypes.cpp ./json/JsonUtils.cpp ./json/JsonValue.cpp ./libs/ft/ato.cpp ./libs/ft/is.cpp ./libs/ft/mem.cpp ./libs/ft/str.cpp ./libs/ft/to.cpp ./log/Logger.cpp ./log/LoggerFactory.cpp ./log/LoggerImpl.cpp ./log/LogLevel.cpp ./main/normal_main.cpp ./main/test_main.cpp ./main.cpp ./net/address/Inet4Address.cpp ./net/address/Inet6Address.cpp ./net/address/InetAddress.cpp ./net/address/InetSocketAddress.cpp ./nio/NIOSelector.cpp ./options/CommandLine.cpp ./options/Option.cpp ./options/OptionParser.cpp ./options/OptionParserException.cpp ./tests/case/TestCase.cpp ./tests/units/unit_encoding_base64.cpp ./tests/units/unit_encoding_chunked.cpp ./tests/units/unit_encoding_identity.cpp ./tests/units/unit_http_parser_headerfields.cpp ./tests/units/unit_http_parser_path.cpp ./tests/units/unit_http_status.cpp ./tests/units/unit_io_file.cpp ./tests/units/unit_libft_ato.cpp ./tests/units/unit_libft_is.cpp ./tests/units/unit_libft_str.cpp ./tests/units/unit_libft_to.cpp ./tests/units/unit_net_address.cpp ./tests/units/unit_nio_selector.cpp ./tests/units/unit_util_buffer.cpp ./tests/units/unit_util_datasize.cpp ./tests/units/unit_util_filedescriptorset.cpp ./tests/units/unit_util_filename.cpp ./tests/units/unit_util_json.cpp ./tests/units/unit_util_number.cpp ./tests/units/unit_util_string.cpp ./unit/DataSize.cpp ./unit/DataUnit.cpp ./util/CharacterUtils.cpp ./util/Closable.cpp ./util/Environment.cpp ./util/FileDescriptorSet.cpp ./util/FilenameUtils.cpp ./util/Number.cpp ./util/Object.cpp ./util/StringUtils.cpp ./util/System.cpp ./util/Time.cpp ./util/URL.cpp
HEADERS					= ./os/detect_platform.h
LIBRARIES				= 
LIBRARIES_BIN			= 

OBJECTS					= $(SOURCES:.cpp=.o)

COMPILER				= clang++

FRAMEWORKS				= 
FLAGS					= -std=c++98 -Wall -Wextra -Werror -g3 -O0
TARGET_REQUIRED_FLAGS	= -I.

MAKE_PREFIX				= "$(COLOR_LIGHT_MAGENTA)[$(COLOR_LIGHT_GREEN) make: $(TARGET) $(COLOR_LIGHT_MAGENTA)]"

ifeq ($(detected_OS),Darwin)
	TOOL_BASE64_DECODE	= base64 -D
else
	TOOL_BASE64_DECODE	= base64 -d
endif

USE_FSANITIZE			= false
RUN_TESTS				= 0

ifeq ($(USE_FSANITIZE),true)
	FLAGS += -fsanitize=address
endif

.cpp.o:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling: $(COLOR_LIGHT_YELLOW)$<$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) -DRUN_TESTS=$(RUN_TESTS) -c $< -o ${<:.cpp=.o}

$(TARGET): libs ${OBJECTS}
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling target: $(COLOR_LIGHT_YELLOW)$(TARGET)$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) $(foreach framework,$(FRAMEWORKS),-framework $(framework)) $(LIBRARIES_BIN) $(OBJECTS) -o $(TARGET)

libs:
	@if [ "$(LIBRARIES)" != "" ]; then make $(LIBRARIES); fi;

all: $(TARGET)
    
fclean: clean
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed target$(COLOR_RESET)"
	@rm -f $(TARGET)
    
clean:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed objects$(COLOR_RESET)"
	@rm -f $(OBJECTS)
	@rm -f $(LIBRARIES_BIN)
	@rm -f gather.py updater.py find_libs.py find_libs_bin.py
    
re: fclean all

$(LIBRARIES):
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling library: $(COLOR_LIGHT_YELLOW)$@$(COLOR_RESET)"
	@make -C $@
	@cp -f $$(ls $(foreach bin,$(LIBRARIES_BIN),$@/$(bin)) 2> /dev/null || true) .

norm:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Calling the norminette...$(COLOR_RESET)"
	@norminette $(SOURCES) $(HEADERS)

run:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Running: ./$(TARGET) $(ARGS) $(COLOR_RESET)"
	@./$(TARGET) $(ARGS)

run-with-valgrind:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Running: valgrind ./$(TARGET) $(ARGS) $(COLOR_RESET)"
	@valgrind $(VALGRIND_ARGS) ./$(TARGET) $(ARGS)
	
gather.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCg0KZGVmIGV4cGxvcmUocGF0aCwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyPUZhbHNlKToNCiAgICBmaWxlcyA9IFtdDQogICAgDQogICAgZm9yIGZpbGUgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgZmlsZSA9IG9zLnBhdGguam9pbihwYXRoLCBmaWxlKQ0KICAgICAgICANCiAgICAgICAgaWYgb3MucGF0aC5pc2ZpbGUoZmlsZSk6DQogICAgICAgICAgICBpZiBsZW4oZXh0ZW5zaW9ucykgIT0gMCBhbmQgb3MucGF0aC5zcGxpdGV4dChmaWxlKVsxXVsxOl0gbm90IGluIGV4dGVuc2lvbnM6DQogICAgICAgICAgICAgICAgY29udGludWUNCiAgICAgICAgICAgIA0KICAgICAgICAgICAgZmlsZXMuYXBwZW5kKGZpbGUpDQogICAgICAgIGVsc2U6DQogICAgICAgICAgICBpZiBnb19kZWVwZXI6DQogICAgICAgICAgICAgICAgZmlsZXMuZXh0ZW5kKGV4cGxvcmUoZmlsZSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKSkNCiAgICANCiAgICByZXR1cm4gZmlsZXMNCg0KDQphcmd2ID0gc3lzLmFyZ3YNCmFyZ2MgPSBsZW4oYXJndikNCg0KaWYgYXJnYyA8IDI6DQogICAgcHJpbnQoInVzYWdlOiB7fSBwYXRoIFsgZXh0ZW5zaW9ucyAuLi4gXSBbIGdvX2RlZXBlciAoYm9vbCkgXSIuZm9ybWF0KGFyZ3ZbMF0pLCBmaWxlPXN5cy5zdGRlcnIpDQogICAgZXhpdCgxKQ0KDQpleHRlbnNpb25zID0gWyBleHRlbnNpb24ucmVwbGFjZSgiLiIsICIiKSBmb3IgZXh0ZW5zaW9uIGluIGFyZ3ZbMjpdIF0NCmdvX2RlZXBlciA9IFRydWUNCg0KaWYgbGVuKGV4dGVuc2lvbnMpICE9IDA6DQogICAgbGFzdCA9IGV4dGVuc2lvbnNbbGVuKGV4dGVuc2lvbnMpIC0gMTpdWzBdDQogICAgDQogICAgaWYgbGFzdCBpbiBbICIwIiwgIjEiLCAidHJ1ZSIsICJmYWxzZSIgXToNCiAgICAgICAgZ29fZGVlcGVyID0gbGFzdCBpbiBbICIxIiwgInRydWUiIF0NCiAgICAgICAgZXh0ZW5zaW9ucyA9IGV4dGVuc2lvbnNbOmxlbihleHRlbnNpb25zKSAtIDFdDQoNCmZpbGVzID0gZXhwbG9yZShhcmd2WzFdLCBleHRlbnNpb25zLCBnb19kZWVwZXIpDQoNCnByaW50KCIgIi5qb2luKGZpbGVzKSkNCg==" | $(TOOL_BASE64_DECODE) > gather.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created gather.py file.$(COLOR_RESET)"
	
updater.py:
	@echo "aW1wb3J0IG9zCmltcG9ydCByZQppbXBvcnQgc3lzCgphcmd2ID0gc3lzLmFyZ3YKYXJnYyA9IGxlbihhcmd2KQoKaWYgYXJnYyA8IDI6CiAgICBwcmludCgidXNhZ2U6IHt9IGtleSA8IHZhbHVlIi5mb3JtYXQoYXJndlswXSksIGZpbGU9c3lzLnN0ZGVycikKICAgIGV4aXQoMSkKCmtleSA9IGFyZ3ZbMV0KdmFsdWUgPSBzeXMuc3RkaW4ucmVhZCgpLnJlcGxhY2UoIlxuIiwgIiIpCgp3aXRoIG9wZW4oIk1ha2VmaWxlIiwgInIiKSBhcyBmaWxlOgogICAgY29udGVudCA9IGZpbGUucmVhZCgpCiAgICAKbGluZXMgPSBbXQoKZm9yIGxpbmUgaW4gY29udGVudC5zcGxpdCgnXG4nKToKICAgIG1hdGNoZXMgPSByZS5maW5kaXRlcihyIiIgKyBrZXkgKyAiKFtcdF0rKS4qJCIsIGxpbmUsIHJlLk1VTFRJTElORSkKICAgIAogICAgZm91bmQgPSBGYWxzZQogICAgCiAgICBmb3IgbWF0Y2ggaW4gbWF0Y2hlczoKICAgICAgICBmb3VuZCA9IFRydWUKICAgICAgICAKICAgICAgICBsaW5lcy5hcHBlbmQoInt9e309IHt9Ii5mb3JtYXQoa2V5LCBtYXRjaC5ncm91cCgxKSwgdmFsdWUpKQogICAgICAgIAogICAgICAgIGJyZWFrCgogICAgaWYgbm90IGZvdW5kOgogICAgICAgIGxpbmVzLmFwcGVuZChsaW5lKQoKd2l0aCBvcGVuKCJNYWtlZmlsZSIsICJ3IikgYXMgZmlsZToKICAgIGZpbGUud3JpdGUoIlxuIi5qb2luKGxpbmVzKSk=" | $(TOOL_BASE64_DECODE) > updater.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created updater.py file.$(COLOR_RESET)"

find_libs.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCmFyZ3YgPSBzeXMuYXJndg0KYXJnYyA9IGxlbihhcmd2KQ0KDQppZiBhcmdjIDwgMjoNCiAgICBwcmludCgidXNhZ2U6IHt9IHBhdGgiLmZvcm1hdChhcmd2WzBdKSwgZmlsZT1zeXMuc3RkZXJyKQ0KICAgIGV4aXQoMSkNCiAgICANCmxpYnJhcmllcyA9IFtdDQoNCmZvciBwYXRoIGluIG9zLmxpc3RkaXIoYXJndlsxXSk6DQogICAgaWYgb3MucGF0aC5pc2RpcihwYXRoKToNCiAgICAgICAgaWYgJ01ha2VmaWxlJyBpbiBvcy5saXN0ZGlyKHBhdGgpOg0KICAgICAgICAgICAgbGlicmFyaWVzLmFwcGVuZChwYXRoKQ0KDQpwcmludCgiICIuam9pbihsaWJyYXJpZXMpKQ0K" | $(TOOL_BASE64_DECODE) > find_libs.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created find_libs.py file.$(COLOR_RESET)"

find_libs_bin.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQppbXBvcnQgcmUNCg0KYXJndiA9IHN5cy5hcmd2DQphcmdjID0gbGVuKGFyZ3YpDQoNClJFR0VYID0gciIoPzpOQU1FfFRBUkdFVClbIFx0XSo9WyBcdF0qKFtcdy5dKylbXHNdIg0KDQppZiBhcmdjIDwgMjoNCiAgICBwcmludCgidXNhZ2U6IHt9IHBhdGgiLmZvcm1hdChhcmd2WzBdKSwgZmlsZT1zeXMuc3RkZXJyKQ0KICAgIGV4aXQoMSkNCiAgICANCmxpYnJhcmllcyA9IFtdDQoNCmZvciBwYXRoIGluIG9zLmxpc3RkaXIoYXJndlsxXSk6DQogICAgaWYgb3MucGF0aC5pc2RpcihwYXRoKToNCiAgICAgICAgbWFrZWZpbGVfcGF0aCA9IG9zLnBhdGguam9pbihwYXRoLCAiTWFrZWZpbGUiKQ0KICAgICAgICANCiAgICAgICAgaWYgb3MucGF0aC5leGlzdHMobWFrZWZpbGVfcGF0aCk6DQogICAgICAgICAgICB3aXRoIG9wZW4obWFrZWZpbGVfcGF0aCwgInIiKSBhcyBmaWxlOg0KICAgICAgICAgICAgICAgIGJpbnMgPSBbXQ0KICAgICAgICAgICAgICAgIA0KICAgICAgICAgICAgICAgIGZvciBtYXRjaCBpbiByZS5maW5kaXRlcihSRUdFWCwgZmlsZS5yZWFkKCksIHJlLk1VTFRJTElORSk6DQogICAgICAgICAgICAgICAgICAgIGJpbnMuYXBwZW5kKG1hdGNoLmdyb3VwKDEpKQ0KICAgICAgICAgICAgICAgIA0KICAgICAgICAgICAgICAgIGlmIGxlbihiaW5zKSA9PSAwOg0KICAgICAgICAgICAgICAgICAgICBwcmludCgie306IHdhcm5pbmc6IG5vIHRhcmdldCBmb3VuZCBmb3IgbGlicmFyeSB7fSIuZm9ybWF0KGFyZ3ZbMF0sIHBhdGgpLCBmaWxlPXN5cy5zdGRlcnIpDQogICAgICAgICAgICAgICAgICAgIGNvbnRpbnVlDQogICAgICAgICAgICAgICAgDQogICAgICAgICAgICAgICAgaWYgbGVuKGJpbnMpID4gMToNCiAgICAgICAgICAgICAgICAgICAgcHJpbnQoInt9OiB3YXJuaW5nOiBtb3JlIHRoYW4gb25lIHRhcmdldCBmb3VuZCBmb3IgbGlicmFyeSB7fSAoe30pIi5mb3JtYXQoYXJndlswXSwgcGF0aCwgYmlucyksIGZpbGU9c3lzLnN0ZGVycikNCiAgICAgICAgICAgICAgICAgICAgDQogICAgICAgICAgICAgICAgbGlicmFyaWVzLmV4dGVuZChiaW5zKQ0KDQpwcmludCgiICIuam9pbihsaWJyYXJpZXMpKQ0K" | $(TOOL_BASE64_DECODE) > find_libs_bin.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created find_libs_bin.py file.$(COLOR_RESET)"

update: gather.py updater.py find_libs.py find_libs_bin.py
	@echo $$(python3 gather.py $(FIX_SOURCES_DIR) $(FIX_SOURCE_EXT) $(FIX_GO_DEEPER)) | python3 updater.py SOURCES
	@echo $$(python3 gather.py $(FIX_HEADERS_DIR) $(FIX_HEADER_EXT) $(FIX_GO_DEEPER)) | python3 updater.py HEADERS
	@echo $$(python3 find_libs.py $(FIX_LIBRARIES_DIR)) | python3 updater.py LIBRARIES
	@echo $$(python3 find_libs_bin.py $(FIX_LIBRARIES_DIR)) | python3 updater.py LIBRARIES_BIN
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Makefile is now up-to-date.$(COLOR_RESET)"

.PHONY: all clean fclean re .c.o norm update $(LIBRARIES)

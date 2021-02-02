/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:33:47 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 16:43:17 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP_
# define CONFIGURATION_HPP_

#include <config/block/RootBlock.hpp>
#include <http/mime/MIMERegistry.hpp>
#include <json/JsonObject.hpp>
#include <string>

#define KEY_DOT "."
#define KEY_ROOT "<root>"
#define KEY_ROOT_MAX_ACTIVE_CLIENT "maxActiveClient"
#define KEY_ROOT_TIMEOUT "timeout"
#define KEY_ROOT_ROOT "root"
#define KEY_ROOT_MIME "mime"
#define KEY_ROOT_CGI "cgi"
#define KEY_ROOT_SERVERS "servers"
#define KEY_MIME_INCLUDES "includes"
#define KEY_MIME_DEFINE "define"
#define KEY_CGI_PATH "path"
#define KEY_CGI_HANDLE_NOT_FOUND "handleNotFound"
#define KEY_CGI_EXTENSIONS  "extensions"
#define KEY_CGI_ENVIRONMENT  "environment"
#define KEY_SERVER_PORT "port"
#define KEY_SERVER_HOST "host"
#define KEY_SERVER_DEFAULT "default"
#define KEY_SERVER_NAME "name"
#define KEY_SERVER_MAXBODYSIZE "maxBodySize"
#define KEY_SERVER_ROOT "root"
#define KEY_SERVER_LOCATIONS "locations"
#define KEY_SERVER_ERRORS "errors"
#define KEY_SERVER_METHODS "methods"
#define KEY_SERVER_LISTING "listing"
#define KEY_SERVER_INDEX_FILES "index"
#define KEY_SERVER_AUTH "auth"
#define KEY_LOCATION_METHODS "methods"
#define KEY_LOCATION_ROOT "root"
#define KEY_LOCATION_LISTING "listing"
#define KEY_LOCATION_INDEX_FILES "index"
#define KEY_LOCATION_CGI "cgi"
#define KEY_LOCATION_AUTH "auth"
#define KEY_AUTH_TYPE "type"
#define KEY_AUTH_REALM "realm"
#define KEY_AUTH_BASIC_USER "user"
#define KEY_AUTH_BASIC_PASSWORD "password"
#define KEY_AUTH_BEARER_TOKEN "token"
#define KEY_LOCATION_MAXBODYSIZE "maxBodySize"

class Configuration
{
	public:
		static Logger &LOG;

	private:
		static Configuration *INSTANCE;

	private:
		std::string m_file;
		const MIMERegistry *m_mimeRegistry;
		const RootBlock *m_rootBlock;

	private:
		Configuration(void);
		Configuration(const Configuration &other);

		Configuration&
		operator=(const Configuration &other);

	public:
		Configuration(const std::string &file, const MIMERegistry &mimeRegistry, const RootBlock &rootBlock);

		virtual
		~Configuration();

		inline const std::string&
		file(void) const
		{
			return (m_file);
		}

		inline const MIMERegistry&
		mimeRegistry(void) const
		{
			return (*m_mimeRegistry);
		}

		inline const RootBlock&
		rootBlock(void) const
		{
			return (*m_rootBlock);
		}

	public:
		static void
		setInstance(Configuration *configuration);

		static Configuration&
		instance();

	public:
		static Configuration*
		fromJsonFile(const std::string &path, bool ignoreMimeIncludesError);

	private:
		class JsonBuilder
		{
			private:
				JsonBuilder();
				JsonBuilder(const JsonBuilder &other);

				virtual
				~JsonBuilder();

				JsonBuilder&
				operator=(const JsonBuilder &other);

			public:
				static const JsonObject&
				rootObject(const std::string &filepath);

				static RootBlock*
				buildRootBlock(const JsonObject &jsonObject);

				static MimeBlock*
				buildMimeBlock(const std::string &path, const JsonObject &jsonObject);

				static CGIBlock*
				buildCGIBlock(const std::string &path, const std::string &key, const JsonObject &jsonObject);

				static ServerBlock*
				buildServerBlock(const std::string &path, const JsonObject &jsonObject);

				static LocationBlock*
				buildLocationBlock(const std::string &path, const std::string &key, const JsonObject &jsonObject);

				static AuthBlock*
				buildAuthBlock(const std::string &path, const JsonObject &jsonObject);

				static CustomErrorMap
				buildCustomErrorMap(const std::string &path, const JsonObject &jsonObject);
		};

		class Validator
		{
			private:
				Validator();
				Validator(const Validator &other);

				virtual
				~Validator();

				JsonBuilder&
				operator=(const Validator &other);

			public:
				static void
				validate(const RootBlock &rootBlock);

				static void
				validate(const RootBlock &rootBlock, const ServerBlock &serverBlock);

				static void
				validate(const RootBlock &rootBlock, const ServerBlock &serverBlock, const LocationBlock &locationBlock);
		};
};

#endif /* CONFIGURATION_HPP_ */

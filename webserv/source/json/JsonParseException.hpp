/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonParseException.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:31:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONPARSEEXCEPTION_HPP_
# define JSONPARSEEXCEPTION_HPP_

#include <json/JsonException.hpp>
#include <json/JsonLocation.hpp>
#include <json/JsonToken.hpp>
#include <string>

class JsonParseException :
		public JsonException
{
	private:
		JsonLocation m_location;

	public:
		JsonParseException();
		JsonParseException(const std::string &message);
		JsonParseException(const std::string &message, const JsonLocation &location);
		JsonParseException(const JsonParseException &other);

		virtual
		~JsonParseException() throw ();

		JsonParseException&
		operator=(const JsonParseException &other);

		const JsonLocation&
		location(void) const;

	public:
		static JsonParseException
		unexpectedChar(char c, const JsonLocation &location);

		static JsonParseException
		expectedChar(char got, char expected, const JsonLocation &location);

		static JsonParseException
		parsing(const JsonToken *token, std::string expectedTokens, const JsonLocation &location);

		static JsonParseException
		expectedEndOfFile(const JsonToken *token, const JsonLocation &location);
};

#endif /* JSONPARSEEXCEPTION_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:28:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/12 00:28:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONREADER_HPP_
# define JSONREADER_HPP_

#include <exception/IllegalStateException.hpp>
#include <exception/IOException.hpp>
#include <json/JsonException.hpp>
#include <json/JsonParser.hpp>
#include <string>

class JsonReader
{
	private:
		bool m_done;
		JsonParser m_parser;

	public:
		JsonReader(void);
		JsonReader(const std::string &source);
		JsonReader(const JsonReader &other);

		virtual
		~JsonReader();

		JsonReader&
		operator=(const JsonReader &other);

	private:
		inline void
		markDone()
		{
			if (m_done)
				throw IllegalStateException("read() already called");

			m_done = true;
		}

		inline JsonException
		internalException(void)
		{
			return (JsonException("Internal error"));
		}

	public:
		JsonValue*
		read(void);

		JsonStructure*
		readStructure(void);

		JsonArray*
		readArray(void);

		JsonObject*
		readObject(void);

	public:
		static JsonReader
		fromFile(const std::string &path) throw (IOException);
};

#endif /* JSONREADER_HPP_ */

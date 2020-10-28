/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:02:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/23 17:02:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONPARSER_HPP_
# define JSONPARSER_HPP_

# include "util/json/JSONType.hpp"

# include <stddef.h>
# include <iostream>

# define JSON_COMMA ','
# define JSON_COLON ':'
# define JSON_LEFTBRACKET '['
# define JSON_RIGHTBRACKET ']'
# define JSON_LEFTBRACE '{'
# define JSON_RIGHTBRACE '}'
# define JSON_QUOTE '"'

class JSONParser
{
	public:
		enum Expect
		{
			E_NULL /*			*/= 0b000000000000001,
			E_TRUE /*			*/= 0b000000000000010,
			E_FALSE /*			*/= 0b000000000000100,
			E_NUMBER /*			*/= 0b000000000001000,
			E_MINUS /*			*/= 0b000000000010000,
			E_DOT /*			*/= 0b000000000100000,
			E_EXPONENTIAL /*	*/= 0b000000001000000,
			E_QUOTE /*			*/= 0b000000010000000,
			E_ARRAY_START /*	*/= 0b000000100000000,
			E_ARRAY_END /*		*/= 0b000001000000000,
			E_OBJECT_START /*	*/= 0b000010000000000,
			E_OBJECT_END /*		*/= 0b000100000000000,
			E_COLON /*			*/= 0b001000000000000,
			E_COMA /*			*/= 0b010000000000000,
			E_END /*			*/= 0b100000000000000,
		};

	private:
		std::string m_source;
		std::size_t m_index;

	public:
		JSONParser(void);
		JSONParser(const std::string &source);
		JSONParser(const JSONParser &other);

		virtual
		~JSONParser();

		JSONParser&
		operator=(const JSONParser &other);

		JSONType
		parse(void);

	private:
		JSONType
		parseElement(void);

		JSONType
		parseBoolean(void);

		JSONType
		parseNull(void);

		JSONType
		parseString(void);

		JSONType
		parseNumber(void);

		JSONType
		parseArray(void);

		JSONType
		parseObject(void);

		void
		skipWhitespaces(void);

		char
		peek(void);

		char
		next(bool escape);

		void
		expect(int mask);

	private:
		void
		throwException(std::string message);
};

#endif /* JSONPARSER_HPP_ */

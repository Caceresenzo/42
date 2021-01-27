/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonParserEvent.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:04:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:04:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONPARSEREVENT_HPP_
# define JSONPARSEREVENT_HPP_

#include <util/Enum.hpp>

class JsonParserEvent :
		public Enum<JsonParserEvent>
{
	public:
		static const JsonParserEvent *START_ARRAY;
		static const JsonParserEvent *START_OBJECT;
		static const JsonParserEvent *KEY_NAME;
		static const JsonParserEvent *VALUE_STRING;
		static const JsonParserEvent *VALUE_NUMBER;
		static const JsonParserEvent *VALUE_TRUE;
		static const JsonParserEvent *VALUE_FALSE;
		static const JsonParserEvent *VALUE_NULL;
		static const JsonParserEvent *END_OBJECT;
		static const JsonParserEvent *END_ARRAY;
};

#endif /* JSONPARSEREVENT_HPP_ */

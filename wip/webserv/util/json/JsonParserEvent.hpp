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
		static JsonParserEvent *START_ARRAY;
		static JsonParserEvent *START_OBJECT;
		static JsonParserEvent *KEY_NAME;
		static JsonParserEvent *VALUE_STRING;
		static JsonParserEvent *VALUE_NUMBER;
		static JsonParserEvent *VALUE_TRUE;
		static JsonParserEvent *VALUE_FALSE;
		static JsonParserEvent *VALUE_NULL;
		static JsonParserEvent *END_OBJECT;
		static JsonParserEvent *END_ARRAY;
};

#endif /* JSONPARSEREVENT_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonEnumValues.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/Enum.hpp>
#include <util/json/JsonParserEvent.hpp>

#define DEFINE_PARSER_EVENT(name) ENUM_DEFINE(JsonParserEvent, name, JsonParserEvent());

DEFINE_PARSER_EVENT(START_ARRAY);
DEFINE_PARSER_EVENT(START_OBJECT);
DEFINE_PARSER_EVENT(KEY_NAME);
DEFINE_PARSER_EVENT(VALUE_STRING);
DEFINE_PARSER_EVENT(VALUE_NUMBER);
DEFINE_PARSER_EVENT(VALUE_TRUE);
DEFINE_PARSER_EVENT(VALUE_FALSE);
DEFINE_PARSER_EVENT(VALUE_NULL);
DEFINE_PARSER_EVENT(END_OBJECT);
DEFINE_PARSER_EVENT(END_ARRAY);

#undef DEFINE_PARSER_EVENT

#include "JsonToken.hpp"

#define DEFINE_TOKEN(name, displayable, event, isValue) ENUM_DEFINE(JsonToken, name, JsonToken(displayable, event, isValue));

DEFINE_TOKEN(CURLYOPEN,/*   */"{",/*      */JsonParserEvent::START_OBJECT,/* */false);
DEFINE_TOKEN(SQUAREOPEN,/*  */"[",/*      */JsonParserEvent::START_ARRAY,/*  */false);
DEFINE_TOKEN(COLON,/*       */":",/*      */NULL,/*                          */false);
DEFINE_TOKEN(COMMA,/*       */",",/*      */NULL,/*                          */false);
DEFINE_TOKEN(STRING,/*      */"String",/* */JsonParserEvent::VALUE_STRING,/* */true);
DEFINE_TOKEN(NUMBER,/*      */"Number",/* */JsonParserEvent::VALUE_NUMBER,/* */true);
DEFINE_TOKEN(TRUE,/*        */"true",/*   */JsonParserEvent::VALUE_TRUE,/*   */true);
DEFINE_TOKEN(FALSE,/*       */"false",/*  */JsonParserEvent::VALUE_FALSE,/*  */true);
DEFINE_TOKEN(NULL_,/*       */"null",/*   */JsonParserEvent::VALUE_NULL,/*   */true);
DEFINE_TOKEN(CURLYCLOSE,/*  */"}",/*      */JsonParserEvent::END_OBJECT,/*   */false);
DEFINE_TOKEN(SQUARECLOSE,/* */"]",/*      */JsonParserEvent::END_ARRAY,/*    */false);
DEFINE_TOKEN(END_OF_FILE,/* */"EOF",/*    */NULL,/*                          */false);

#undef DEFINE_TOKEN

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationBindException.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATIONBINDEXCEPTION_HPP_
# define CONFIGURATIONBINDEXCEPTION_HPP_

#include <config/exceptions/ConfigurationException.hpp>
#include <json/JsonType.hpp>
#include <json/JsonValue.hpp>
#include <string>

class ConfigurationBindException :
		public ConfigurationException
{
	public:
		ConfigurationBindException();
		ConfigurationBindException(const std::string &message);
		ConfigurationBindException(const ConfigurationBindException &other);

		virtual
		~ConfigurationBindException() throw ();

		ConfigurationBindException&
		operator=(const ConfigurationBindException &other);

	public:
		template<typename T>
			static inline ConfigurationBindException
			uncastable(const std::string &path, const JsonValue &jsonValue)
			{
				return (ConfigurationBindException("cannot cast " + jsonValue.typeString() + " to " + JsonTypeTraits<T>::typeString + " (" + path + ")"));
			}

		template<typename T1, typename T2>
			static inline ConfigurationBindException
			uncastable2(const std::string &path, const JsonValue &jsonValue)
			{
				return (ConfigurationBindException("cannot cast " + jsonValue.typeString() + " to " + JsonTypeTraits<T1>::typeString + " or " + JsonTypeTraits<T2>::typeString + " (" + path + ")"));
			}

};

#endif /* CONFIGURATIONBINDEXCEPTION_HPP_ */

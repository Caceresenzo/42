/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationValidateException.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATIONVALIDATEEXCEPTION_HPP_
# define CONFIGURATIONVALIDATEEXCEPTION_HPP_

#include <config/exceptions/ConfigurationException.hpp>
#include <string>

class ConfigurationValidateException :
		public ConfigurationException
{
	public:
		ConfigurationValidateException();
		ConfigurationValidateException(const std::string &message);
		ConfigurationValidateException(const ConfigurationValidateException &other);

		virtual
		~ConfigurationValidateException() throw ();

		ConfigurationValidateException&
		operator=(const ConfigurationValidateException &other);
};

#endif /* CONFIGURATIONVALIDATEEXCEPTION_HPP_ */

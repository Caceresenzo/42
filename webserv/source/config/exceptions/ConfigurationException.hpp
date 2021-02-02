/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationException.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATIONEXCEPTION_HPP_
# define CONFIGURATIONEXCEPTION_HPP_

#include <exception/RuntimeException.hpp>
#include <string>

class ConfigurationException :
		public RuntimeException
{
	public:
		ConfigurationException();
		ConfigurationException(const std::string &message);
		ConfigurationException(const ConfigurationException &other);

		virtual
		~ConfigurationException() throw ();

		ConfigurationException&
		operator=(const ConfigurationException &other);
};

#endif /* CONFIGURATIONEXCEPTION_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Option.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:29:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 19:29:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_HPP_
# define OPTION_HPP_

#include <iostream>

class IOptionValidator;

#if 1
#include <util/options/OptionValidator.hpp>
#endif

class Option
{
	private:
		char m_short;
		std::string m_long;
		std::string m_name;
		std::string m_description;
		std::string m_parameters;
		std::string m_value;
		IOptionValidator *validator;

	public:
		Option();
		Option(const Option &other);

		virtual
		~Option();

		Option&
		operator=(const Option &other);
};

#endif /* OPTION_HPP_ */

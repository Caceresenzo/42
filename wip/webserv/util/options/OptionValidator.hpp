/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionValidator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:31:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 19:31:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONVALIDATOR_HPP_
# define OPTIONVALIDATOR_HPP_

#include <iostream>

class IOptionValidator
{
	public:
		virtual
		~IOptionValidator();

		virtual std::string
		validate(const std::string &value) const = 0;
};

class StringOptionValidator :
		public IOptionValidator
{
		virtual
		~StringOptionValidator();

		virtual std::string
		validate(const std::string &value) const;
};

class NumericOptionValidator :
		public IOptionValidator
{
		virtual
		~NumericOptionValidator();

		virtual std::string
		validate(const std::string &value) const;
};

#endif /* OPTIONVALIDATOR_HPP_ */

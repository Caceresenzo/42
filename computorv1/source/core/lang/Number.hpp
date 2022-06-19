/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:58:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 23:58:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_HPP_
# define NUMBER_HPP_

#include <iostream>
#include <sstream>
#include <string>

class Number
{
	public:
		template<typename T>
			static T
			abs(T value)
			{
				if (value < 0)
					return (-value);

				return (value);
			}

		template<typename T>
			static std::string
			to_string(T value)
			{
				std::stringstream stream;
				stream << value;

				return (stream.str());
			}
};

#endif /* NUMBER_HPP_ */

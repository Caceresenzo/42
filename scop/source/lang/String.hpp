/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   String.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:16:00 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 22:16:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_HPP_
# define STRING_HPP_

#include <string>
#include <sstream>

class String
{
	public:
		template<typename T>
			static std::string
			value_of(const T &value)
			{
				std::stringstream stream;

				stream << value;

				return (stream.str());
			}
};

#endif /* STRING_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:58:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 23:58:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Number.hpp"

template<>
	std::string
	Number::to_string<long double>(long double value)
	{
		std::stringstream stream;

		if (value == 0.0 || value == -0.0)
			stream << 0.0;
		else
			stream << value;

		return (stream.str());
	}


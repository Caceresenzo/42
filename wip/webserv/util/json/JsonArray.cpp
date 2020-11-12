/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:55:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:55:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonArray.hpp"

const std::string
JsonArray::toJsonString(void) const
{
	std::string out;

	const_iterator it = m_value.begin();
	const_iterator ite = m_value.end();

	out += '[';

	while (it != ite)
	{
		out += (*it)->toJsonString();

		if (++it != ite)
			out += ',';
	}

	out += ']';

	return (out);
}

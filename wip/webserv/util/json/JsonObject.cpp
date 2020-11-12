/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:31:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonObject.hpp"

#include "JsonUtils.hpp"

const std::string
JsonObject::toJsonString() const
{
	std::string out;

	const_iterator it = m_value.begin();
	const_iterator ite = m_value.end();

	out += '{';

	while (it != ite)
	{
		out += JsonUtils::escapeString(it->first);
		out += ':';
		out += it->second->toJsonString();

		if (++it != ite)
			out += ',';
	}

	out += '}';

	return (out);
}

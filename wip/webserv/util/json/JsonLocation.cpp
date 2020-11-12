/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonLocation.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonLocation.hpp"

JsonLocation JsonLocation::UNKNOWN = JsonLocation();

std::ostream&
operator<<(std::ostream &stream, const JsonLocation &location)
{
	return (stream << "line: " << location.line() << ", column: " << location.column() << ", index: " << location.index());
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHTTPBodyDecoder.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:00:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/13 16:26:16 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/body/encoding/IHTTPBodyDecoder.hpp>
#include <iostream>

IHTTPBodyDecoder::~IHTTPBodyDecoder()
{
}

std::string
IHTTPBodyDecoder::decode(const std::string &input, bool max)
{
	std::string out;

	size_t consumed = 0;
	consume(input, out, consumed, max);

	return (out);
}

void
IHTTPBodyDecoder::cleanup()
{
}

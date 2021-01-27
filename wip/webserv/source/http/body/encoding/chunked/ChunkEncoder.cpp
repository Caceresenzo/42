/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkEncoder.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:51:33 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/23 18:29:30 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/body/encoding/chunked/ChunkEncoder.hpp>
#include <http/HTTP.hpp>
#include <util/Convert.hpp>

const std::string ChunkEncoder::ZERO = "0\r\n\r\n";

ChunkEncoder::ChunkEncoder()
{
}

ChunkEncoder::~ChunkEncoder()
{
}

std::string
ChunkEncoder::encode(const std::string &input)
{
	if (input.empty())
		return (ZERO);

	return (staticEncode(input) + ZERO);
}

std::string
ChunkEncoder::staticEncode(const std::string &input)
{
	return (Convert::toString(input.size(), 16) + HTTP::CRLF + input + HTTP::CRLF);
}

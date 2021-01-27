/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPBodyEncoding.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:32:18 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 18:18:52 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/body/encoding/chunked/ChunkDecoder.hpp>
#include <http/body/encoding/exception/HTTPBodyEncodingException.hpp>
#include <http/body/encoding/HTTPBodyEncoding.hpp>
#include <http/body/encoding/identity/IdentityDecoder.hpp>
#include <util/Number.hpp>
#include <util/Optional.hpp>
#include <string>

HTTPBodyEncoding::~HTTPBodyEncoding()
{
}

IHTTPBodyDecoder*
HTTPBodyEncoding::decoderFor(const HTTPHeaderFields &headerFields)
{
	Optional<std::string> transfertEncodingOpt = headerFields.get(HTTPHeaderFields::TRANSFER_ENCODING);
	if (transfertEncodingOpt.present())
	{
		const std::string &transfertEncoding = transfertEncodingOpt.get();

		if (transfertEncoding == HTTPHeaderFields::CHUNKED)
			return (new ChunkDecoder(true));

		throw HTTPBodyEncodingException("unsupported transfert-encoding:" + transfertEncoding);
	}

	Optional<std::string> contentLengthOpt = headerFields.get(HTTPHeaderFields::CONTENT_LENGTH);
	if (contentLengthOpt.present())
	{
		const std::string &contentLength = contentLengthOpt.get();

		try
		{
			long long length = Number::parse<long long>(contentLength);

			if (length == 0)
				return (NULL);

			return (new IdentityDecoder(true, length));
		}
		catch (Exception &exception)
		{
			throw HTTPBodyEncodingException("content-length `" + contentLength + "` is not a valid number: " + exception.message());
		}
	}

	throw HTTPBodyEncodingException("no transfert-encoding or content-length");
}

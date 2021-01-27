/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPBodyEncoding.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:32:18 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 18:18:59 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPBODYENCODING_HPP_
# define HTTPBODYENCODING_HPP_

#include <http/header/HTTPHeaderFields.hpp>

class IHTTPBodyDecoder;

class HTTPBodyEncoding
{
	private:
		HTTPBodyEncoding();
		HTTPBodyEncoding(const HTTPBodyEncoding &other);

		HTTPBodyEncoding&
		operator=(const HTTPBodyEncoding &other);

	public:
		virtual
		~HTTPBodyEncoding();

	public:
		static IHTTPBodyDecoder*
		decoderFor(const HTTPHeaderFields &headerFields);
};

#endif /* HTTPBODYENCODING_HPP_ */

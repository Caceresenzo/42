/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IdentityDecoder.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:26:21 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 18:19:28 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTITYDECODER_HPP_
# define IDENTITYDECODER_HPP_

#include <http/body/encoding/IHTTPBodyDecoder.hpp>
#include <util/Singleton.hpp>
#include <exception/Exception.hpp>

class IdentityDecoder :
		public IHTTPBodyDecoder
{
	private:
		bool m_isAllocated;
		long long m_contentLength;
		long long m_consumed;
	
	private:
		IdentityDecoder();
		IdentityDecoder(const IdentityDecoder &other);

		IdentityDecoder&
		operator=(const IdentityDecoder &other);

	public:
		IdentityDecoder(bool isAllocated, long long contentLength);

		virtual
		~IdentityDecoder();

		bool
		consume(const std::string &in, std::string &out, size_t &consumed, bool max);

		void
		cleanup();
};

#endif /* IDENTITYDECODER_HPP_ */

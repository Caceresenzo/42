/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IdentityEncoder.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:24:18 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/09 01:24:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDENTITYENCODER_HPP_
# define IDENTITYENCODER_HPP_

#include <http/body/encoding/IHTTPBodyEncoder.hpp>
#include <util/Singleton.hpp>
#include <string>

class IdentityEncoder :
		public IHTTPBodyEncoder,
		public Singleton<IdentityEncoder>
{
	private:
		IdentityEncoder(const IdentityEncoder &other);

		IdentityEncoder&
		operator=(const IdentityEncoder &other);

	public:
		IdentityEncoder();

		virtual
		~IdentityEncoder();

		std::string
		encode(const std::string &input);
};

#endif /* IDENTITYENCODER_HPP_ */

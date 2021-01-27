/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthBlock.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:16:20 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/28 17:16:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTHBLOCK_HPP_
# define AUTHBLOCK_HPP_

#include <util/Optional.hpp>
#include <string>

class Authorization;

class AuthBlock
{
	private:
		Optional<std::string> m_realm;

	private:
		AuthBlock(const AuthBlock &other);

		AuthBlock&
		operator=(const AuthBlock &other);

	public:
		AuthBlock();

		virtual
		~AuthBlock();

		AuthBlock&
		realm(const std::string &realm);

		virtual bool
		authorize(const std::string &credentials) const = 0;

		virtual const std::string&
		type() const = 0;

		virtual const std::string&
		prettyType() const = 0;

		inline const Optional<std::string>&
		realm() const
		{
			return (m_realm);
		}
};

#endif /* AUTHBLOCK_HPP_ */

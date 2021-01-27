/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BasicAuthBlock.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:16:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/28 17:16:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICAUTHBLOCK_HPP_
# define BASICAUTHBLOCK_HPP_

#include <config/block/AuthBlock.hpp>

class BasicAuthBlock :
		public AuthBlock
{
	public:
		static const std::string TYPE;
		static const std::string PRETTY_TYPE;

	private:
		std::string m_user;
		Optional<std::string> m_password;

	private:
		BasicAuthBlock();
		BasicAuthBlock(const BasicAuthBlock &other);

		BasicAuthBlock&
		operator=(const BasicAuthBlock &other);

	public:
		BasicAuthBlock(const std::string &user);

		virtual
		~BasicAuthBlock();

		BasicAuthBlock&
		password(const std::string &password);

		bool
		authorize(const std::string &credentials) const;

		const std::string&
		type() const;

		const std::string&
		prettyType() const;

		inline const std::string&
		user() const
		{
			return (m_user);
		}

		inline const Optional<std::string>&
		password() const
		{
			return (m_password);
		}
};

#endif /* BASICAUTHBLOCK_HPP_ */

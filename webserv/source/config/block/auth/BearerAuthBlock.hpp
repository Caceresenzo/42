/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BearerAuthBlock.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:16:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/28 17:16:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BearerAuthBlock_HPP_
# define BearerAuthBlock_HPP_

#include <config/block/AuthBlock.hpp>

class BearerAuthBlock :
		public AuthBlock
{
	public:
		static const std::string TYPE;
		static const std::string PRETTY_TYPE;

	private:
		std::string m_token;

	private:
		BearerAuthBlock();
		BearerAuthBlock(const BearerAuthBlock &other);

		BearerAuthBlock&
		operator=(const BearerAuthBlock &other);

	public:
		BearerAuthBlock(const std::string &token);

		virtual
		~BearerAuthBlock();

		bool
		authorize(const std::string &credentials) const;

		const std::string&
		type() const;

		const std::string&
		prettyType() const;

		inline const std::string&
		token() const
		{
			return (m_token);
		}
};

#endif /* BearerAuthBlock_HPP_ */

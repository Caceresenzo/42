/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CharacterUtils.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:16:40 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/05 01:16:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTERUTILS_HPP_
# define CHARACTERUTILS_HPP_

#include <cctype>

class CharacterUtils
{
	private:
		CharacterUtils();
		CharacterUtils(const CharacterUtils &other);

		virtual
		~CharacterUtils();

		CharacterUtils&
		operator=(const CharacterUtils &other);

	public:
		struct InsensitiveCompare
		{
			public:
				bool
				operator()(const unsigned char &c1, const unsigned char &c2) const;
		};
};

#endif /* CHARACTERUTILS_HPP_ */

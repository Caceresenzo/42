/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberToken.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:51:54 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 14:51:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBERTOKEN_HPP_
# define NUMBERTOKEN_HPP_

#include "Token.hpp"
#include "Fixed.hpp"

class NumberToken : public Token
{
	private:
		Fixed _value;

	public:
		NumberToken();
		NumberToken(const Fixed fixed);
		NumberToken(const NumberToken &other);

		virtual ~NumberToken();

		NumberToken& operator=(const NumberToken &other);

		const std::string toString(void) const;

		const Fixed getValue() const;
};

#endif /* NUMBERTOKEN_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParenthesisCloseToken.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENTHESISCLOSETOKEN_HPP_
# define PARENTHESISCLOSETOKEN_HPP_

# include "Token.hpp"

class ParenthesisCloseToken : public Token
{
	public:
		ParenthesisCloseToken();
		ParenthesisCloseToken(const ParenthesisCloseToken &other);

		virtual ~ParenthesisCloseToken();

		ParenthesisCloseToken& operator=(const ParenthesisCloseToken &other);

		virtual Token* clone() const;
		virtual std::string toString() const;
};

#endif /* PARENTHESISCLOSETOKEN_HPP_ */

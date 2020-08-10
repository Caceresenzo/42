/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParenthesisOpenToken.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENTHESISOPENTOKEN_HPP_
# define PARENTHESISOPENTOKEN_HPP_

# include "Token.hpp"

class ParenthesisOpenToken : public Token
{
	public:
		ParenthesisOpenToken();
		ParenthesisOpenToken(const ParenthesisOpenToken &other);

		virtual ~ParenthesisOpenToken();

		ParenthesisOpenToken& operator=(const ParenthesisOpenToken &other);

		virtual Token* clone() const;
		virtual std::string toString() const;
};

#endif /* PARENTHESISOPENTOKEN_HPP_ */

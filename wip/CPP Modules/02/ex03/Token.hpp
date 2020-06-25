/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:05:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 14:05:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP_
# define TOKEN_HPP_

# include <string>

enum TokenType
{
	TT_END_OF_FILE = -1,
	TT_NUMBER = 0,
	TT_PLUS,
	TT_MINUS,
	TT_ASTERISK,
	TT_SLASH,
	TT_ROUND_BRACKET_OPEN,
	TT_ROUND_BRACKET_CLOSE,
	TT__SIZE
};

class Token
{
	private:
		TokenType _type;
		std::size_t _position;

	public:
		Token();
		Token(const Token &other);
		Token(TokenType type);

		virtual ~Token();

		Token& operator=(const Token &other);

		TokenType type() const;
		std::string name() const;

		std::size_t position() const;
		std::size_t position(std::size_t position);

		virtual const std::string toString(void) const;

		static bool isOperator(TokenType type);
		static std::string typeName(TokenType type);
};

#endif /* TOKEN_HPP_ */

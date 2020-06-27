/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <unistd.h>

# include "Token.hpp"

class Lexer
{
	private:
		std::string _expression;
		char _currentChar;
		ssize_t _currentPosition;
		std::string _error;

	public:
		Lexer(void);
		Lexer(const Lexer &other);
		Lexer(std::string expression);

		~Lexer(void);

		Lexer& operator =(const Lexer &other);

		void nextChar(void);
		char peek(void);

		void skipWhitespace(void);

		Token *getToken(void);

		void abort(std::string error);
		bool aborted(void);

		ssize_t position();
		std::string getError(void);
};

#endif /* LEXER_HPP_ */

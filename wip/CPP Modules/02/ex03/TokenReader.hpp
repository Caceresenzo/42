/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenReader.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:55:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 15:55:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENREADER_HPP_
# define TOKENREADER_HPP_

# include "ArrayList.hpp"
# include "Token.hpp"
# include "Fixed.hpp"

class TokenReader
{
	private:
		ArrayList *_list;
		size_t _index;
		Token *_currentToken;
		Token *_peekToken;
		std::string _error;
		std::size_t _errorPosition;
		int _depth;

	public:
		TokenReader(void);
		TokenReader(ArrayList &list);
		TokenReader(const TokenReader &other);

		virtual ~TokenReader(void);

		TokenReader& operator =(const TokenReader &other);

		bool checkToken(TokenType type);
		bool checkPeek(TokenType type);

		void nextToken(void);
		void previousToken(void);

		Fixed evaluate(void);

		void dive(void);
		bool surface(void);

		bool abort(std::string error);
		bool abortNowhere(std::string error);
		bool abort(std::string error, std::size_t at);
		bool aborted(void);

		std::string getError(void);
		std::size_t getErrorPosition(void);

		Token *currentToken() const;
		int depth() const;
		const ArrayList *list() const;
};

#endif /* TOKENREADER_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:55:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 15:55:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP_
# define PARSER_HPP_

# include "ArrayList.hpp"
# include "Token.hpp"
# include "TokenReader.hpp"

class Parser : public TokenReader
{
	public:
		Parser(void);
		Parser(ArrayList &list);
		Parser(const Parser &other);

		virtual ~Parser(void);

		Parser& operator =(const Parser &other);

		bool parseLine();
		bool parseExpression();
		bool parseExpressionBody();
};

#endif /* PARSER_HPP_ */

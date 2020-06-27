/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <string>

#include "ArrayList.hpp"
#include "Evaluator.hpp"
#include "Fixed.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Token.hpp"

#define PROGRAM_NAME "eval_expr"

void
error_invalid_expression(std::string reason, std::string expr, std::size_t at)
{
	std::cerr << "\e[97mError: \e[91m" << reason << ".\e[0m" << std::endl;
	std::cerr << expr << std::endl;

	if (at != std::string::npos)
	{
		std::cerr << "\e[1m\e[92m";

		for (size_t index = 0; index < at; index++)
			std::cerr << " ";

		std::cerr << "^" << "\e[0m" << std::endl;
	}
}

bool
error_invalid_expression(std::string expression, TokenReader &reader)
{
	std::string reason = reader.getError();

	if (!reader.aborted())
		reason = "no reason";

	error_invalid_expression(reason, expression, reader.getErrorPosition());

	return (false);
}

bool
eval_expr(std::string &expr, Fixed *fixed)
{
	Lexer lexer = Lexer(expr);
	ArrayList list = ArrayList();

	Token *token;
	while (true)
	{
		token = lexer.getToken();

		if (lexer.aborted() || !token)
			break;

		list.add(token);

		if (token->type() == TT_END_OF_FILE)
			break;
	}

	if (lexer.aborted())
	{
		error_invalid_expression(lexer.getError(), expr, lexer.position());
		return (false);
	}

	if (!(list.empty() || list.first()->type() == TT_END_OF_FILE))
	{
		Parser parser = Parser(list);
		if (!parser.parseLine() || parser.aborted())
			return (error_invalid_expression(expr, parser));

		Evaluator evaluator = Evaluator(list);

		*fixed = evaluator.evaluate();

		if (evaluator.aborted())
			return (error_invalid_expression(expr, evaluator));
	}

	return (true);
}

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: " << PROGRAM_NAME << " <expression>" << std::endl;
		return (1);
	}

	std::string expr = std::string(argv[1]);
	Fixed result = Fixed();

	bool success = eval_expr(expr, &result);

	if (success)
		std::cout << result << std::endl;

	return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}

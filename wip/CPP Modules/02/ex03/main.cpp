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

#include <iostream>
#include <iomanip>

#include "Token.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Evaluator.hpp"
#include "Fixed.hpp"

#define PROGRAM_NAME "eval_expr"

void
error_invalid_expression(std::string reason, std::string expression,
                         size_t index)
{
	std::cerr << "\e[97mError: \e[91m" << reason << ".\e[0m" << std::endl;
	std::cerr << expression << std::endl;
	std::cerr << "\e[1m\e[92m" << std::setw(index) << "^" << "\e[0m"
	        << std::endl;

	exit(1);
}

#include "libft.hpp"

int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: " << PROGRAM_NAME << " <expression>" << std::endl;
		return (1);
	}

	std::string expression = std::string(argv[1]);
	t_list *head = NULL;

	Lexer lexer(expression);
	if (!lexer.analyze(head))
	{
		error_invalid_expression("Invalid token", lexer.getExpression(), lexer.getCurrentIndex());
	}

	Fixed result;

	if (ft_lstsize(head) != 0)
	{

		Token *root = new Token(head, (size_t)-1);
		Token **tokens = root->convertListToArray();

		Parser parser(tokens);
		if (!parser.parse())
		{
			error_invalid_expression( parser.getErrorReason(), expression, parser.getProblematicToken()->getPositionInString());
		}

		Evaluator evaluator;
		result = evaluator.evaluate(tokens);

		if (evaluator.hasFoundError())
		{
			error_invalid_expression(evaluator.getErrorReason(), expression, evaluator.getProblemPosition());
		}

		delete root;
	}

	std::cout << result << std::endl;

	return (0);
}

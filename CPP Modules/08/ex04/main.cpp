/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:29:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:29:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

#include "MutantStack.hpp"
#include "NumericToken.hpp"
#include "OperatorToken.hpp"
#include "PostfixConvertor.hpp"
#include "Token.hpp"
#include "TokenParser.hpp"

bool
compute(std::vector<Token*> &tokens, std::vector<Token*> &postfixTokens)
{
	bool everything = false;

	try
	{
		MutantStack<int> stack;
		for (size_t index = 0; index < postfixTokens.size(); ++index)
		{
			Token *token = postfixTokens[index];

			std::cout << "I " << std::setw(20) << std::left << token;
			std::cout << " | OP " << std::setw(10) << std::left;

			NumericToken *numericToken;
			OperatorToken *operatorToken;

			if ((numericToken = dynamic_cast<NumericToken*>(token)))
			{
				std::cout << "Push";

				stack.push(numericToken->value());
			}
			else if ((operatorToken = dynamic_cast<OperatorToken*>(token)))
			{
				std::cout << operatorToken->english();

				if (stack.size() < 2)
					throw PostfixConvertor::PostfixException("cannot use operator (stack size < 2)");

				int left = stack.top();
				stack.pop();

				int right = stack.top();
				stack.pop();

				stack.push(operatorToken->use(right, left));
			}

			std::cout << " | ST ";

			bool first = true;
			for (MutantStack<int>::reverse_iterator it = stack.rbegin();
			        it < stack.rend(); ++it)
			{
				if (!first)
					std::cout << ", ";

				std::cout << *it;

				first = false;
			}

			std::cout << "]" << std::endl;
		}

		everything = true;
		int result = 0;
		if (!postfixTokens.empty())
		{
			if (stack.size() != 1)
				throw PostfixConvertor::PostfixException("cannot get result (stack size != 1)");

			result = stack.top();

			std::cout << std::endl;
		}

		std::cout << "Result of '" << TokenParser::pretty(tokens) << "' = " << result << std::endl;
	}
	catch (std::exception &e)
	{
		if (!everything)
			std::cout << " | ";
		std::cout << "ERROR: " << e.what() << std::endl;

		std::cout << std::endl;
		std::cout << "Failed to compute: " << TokenParser::pretty(tokens) << std::endl;

		return (false);
	}

	return (true);
}

int
main(int argc, char **argv)
{
	std::string program = argv[0];

	if (argc != 2)
	{
		std::cout << "usage: " << program << " <expr>" << std::endl;
		return (EXIT_FAILURE);
	}

	std::vector<Token*> tokens;
	std::vector<Token*> postfixTokens;

	bool success = false;

	if (TokenParser(argv[1]).parse(tokens))
	{
		if (PostfixConvertor(&tokens).convert(postfixTokens))
		{
			std::cout << "Tokens: " << Token::join(tokens) << std::endl;
			std::cout << "Postfix: " << Token::join(postfixTokens) << std::endl;

			std::cout << std::endl;

			success = compute(tokens, postfixTokens);
		}
	}

	Token::free(tokens);
	Token::free(postfixTokens);

	return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}

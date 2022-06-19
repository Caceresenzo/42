/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:10:47 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 19:10:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/parse/ExpressionParser.hpp>
#include <computor/parse/ParseException.hpp>
#include <computor/Polynomial.hpp>
#include <computor/resolve/PolynomialResolver.hpp>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>


int
main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << " <expression>" << std::endl;
		return (1);
	}

	std::string input = argv[1];

	std::pair<Polynomial<>, Polynomial<> > equation;
	try
	{
		equation = ExpressionParser::parse(input);
	}
	catch (ParseException &exception)
	{
		std::cerr << exception.message() << std::endl;

		if (exception.at() != std::string::npos)
		{
			std::cerr << input << std::endl;
			std::cerr << std::setw(exception.at() + 1) << std::right << "^" << std::endl;
		}

		return (1);
	}

	Polynomial<> &left = equation.first;
	Polynomial<> &right = equation.second;

	if (left == right)
	{
		std::cout << "The polynomial is identical, all numbers can be used as solution." << std::endl;
		return (0);
	}

	Polynomial<> reduced = Polynomial<>::reduce(left, right);
	std::cout << "Reduced form: " << reduced << std::endl;

	int degree = reduced.degree();
	std::cout << "Polynomial degree: " << degree << std::endl;

	const PolynomialResolver &resolver = PolynomialResolver::get_impl(reduced);

	if (!resolver.resolve(reduced))
		return (1);

	return (0);
}

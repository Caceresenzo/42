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
#include <core/util/Optional.hpp>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
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

//	Polynomial<> left = Polynomial<>::quadratic(-9.3, 4, 5);
//	Polynomial<> right = Polynomial<>::constant(1);

////	// 42 * X^0 = 42 * X^0
//	Polynomial<> left = Polynomial<>::constant(42);
//	Polynomial<> right = Polynomial<>::constant(42);

//	// 5 * X^0 + 4 * X^1 = 4 * X^0
//	Polynomial<> left = Polynomial<>::linear(4, 5);
//	Polynomial<> right = Polynomial<>::constant(4);

//	// 8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0
//	Polynomial<> left = Polynomial<>::cubic(-5.6, 0, -6, 8);
//	Polynomial<> right = Polynomial<>::constant(3);

//	// from: https://homeomath2.imingo.net/images/equasec.gif
//	Polynomial<> left = Polynomial<>::quadratic(3, -1, -10);
//	Polynomial<> right = Polynomial<>::zero();

//	// 0 = 0
//	Polynomial<> left = Polynomial<>::zero();
//	Polynomial<> right = Polynomial<>::zero();

	if (left == right)
	{
		std::cout << "The polynomial is identical, all numbers can be used as solution." << std::endl;
		return (0);
	}

	Polynomial<> reduced = Polynomial<>::reduce(left, right);
	std::cout << "Reduced form: " << reduced << std::endl;

	int degree = reduced.degree();
	std::cout << "Polynomial degree: " << degree << std::endl;

	if (degree == -1)
	{
		std::cout << "The solution is undefined" << std::endl;

		return (0);
	}

	if (degree == 0)
	{
		std::cout << "The solution is:" << std::endl;
		std::cout << "0" << std::endl;

		return (0);
	}

	if (degree == 1)
	{
		long double b = reduced.find(0).or_else(0);
		long double a = reduced.find(1).or_else(0);

		if (a == 0) /* should not happen */
		{
			std::cerr << "ERR: a == 0" << std::endl;
			return (1);
		}

		long double soluce = -b / a;

		std::cout << "The solution is:" << std::endl;
		std::cout << soluce << std::endl;

		return (0);
	}

	if (degree == 2)
	{
		long double a = reduced.find(2).or_else(0);
		long double b = reduced.find(1).or_else(0);
		long double c = reduced.find(0).or_else(0);

		if (a == 0) /* should not happen */
		{
			std::cerr << "ERR: a == 0" << std::endl;
			return (1);
		}

		long double delta = (b * b) - (4 * a * c);

		if (delta > 0)
		{
			std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;

			long double delta_sqrt = std::sqrt(delta);

			long double x1 = (-b - delta_sqrt) / (2 * a);
			long double x2 = (-b + delta_sqrt) / (2 * a);

			std::cout << x1 << std::endl;
			std::cout << x2 << std::endl;

			return (0);
		}

		if (delta == 0)
		{
			std::cout << "Discriminant is equal to zero, the solution is:" << std::endl;

			long double x = -b / (2 * a);

			std::cout << x << std::endl;

			return (0);
		}

		if (delta < 0)
		{
			std::cout << "Discriminant is strictly negative, the solution is:" << std::endl;

			long double b_negated = -b;
			long double delta_sqrt = std::sqrt(-delta);
			long double a_x2 = 2 * a;

			std::cout << "(" << b_negated << " - i - " << delta_sqrt << ") / " << a_x2 << std::endl;

			return (0);
		}

		std::cerr << "ERR: no condition matched??" << delta << std::endl;
		return (1);
	}

	if (degree > 2)
	{
		std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
		return (0);
	}

	std::cerr << "ERR: unhandled degree: " << degree << std::endl;
	return (1);
}

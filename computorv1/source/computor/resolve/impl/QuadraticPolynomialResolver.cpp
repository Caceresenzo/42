/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuadraticPolynomialResolver.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:06:39 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:06:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/Polynomial.hpp>
#include <computor/resolve/impl/QuadraticPolynomialResolver.hpp>
#include <core/lang/Math.hpp>
#include <core/lang/Number.hpp>
#include <core/util/Optional.hpp>
#include <cmath>
#include <iostream>
#include <string>

QuadraticPolynomialResolver::~QuadraticPolynomialResolver()
{
}

bool
QuadraticPolynomialResolver::resolve(const polynomial_type &polynomial) const
{
	long double a = polynomial.find(2).or_else(0);
	long double b = polynomial.find(1).or_else(0);
	long double c = polynomial.find(0).or_else(0);

	if (a == 0) /* should not happen */
	{
		std::cerr << "ERR: a == 0" << std::endl;
		return (false);
	}

	long double delta = (b * b) - (4 * a * c);

//		std::cout << "delta=" << delta << std::endl;

	if (delta > 0)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;

		long double delta_sqrt = Math::sqrt(delta);

		long double x1 = (-b - delta_sqrt) / (2 * a);
		long double x2 = (-b + delta_sqrt) / (2 * a);

		std::cout << Number::to_string(x1) << std::endl;
		std::cout << Number::to_string(x2) << std::endl;

		return (true);
	}

	if (delta == 0)
	{
		std::cout << "Discriminant is equal to zero, the solution is:" << std::endl;

		long double x = -b / (2 * a);

		std::cout << Number::to_string(x) << std::endl;

		return (true);
	}

	if (delta < 0)
	{
		std::cout << "Discriminant is strictly negative, the solution is:" << std::endl;

		long double b_negated = -b;
		long double delta_sqrt = Math::sqrt(-delta);
		long double a_x2 = 2 * a;

		std::cout << "(" << Number::to_string(b_negated) << " - i - " << Number::to_string(delta_sqrt) << ") / " << Number::to_string(a_x2) << std::endl;

		return (true);
	}

	std::cerr << "ERR: no condition matched??" << Number::to_string(delta) << std::endl;
	return (false);
}

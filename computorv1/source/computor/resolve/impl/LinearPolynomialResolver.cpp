/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearPolynomialResolver.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:05:00 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:05:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/resolve/impl/LinearPolynomialResolver.hpp>

LinearPolynomialResolver::~LinearPolynomialResolver()
{
}

bool
LinearPolynomialResolver::resolve(const polynomial_type &polynomial) const
{
	long double b = polynomial.find(0).or_else(0);
	long double a = polynomial.find(1).or_else(0);

	if (a == 0) /* should not happen */
	{
		std::cerr << "ERR: a == 0" << std::endl;
		return (false);
	}

	long double soluce = -b / a;

	std::cout << "The solution is:" << std::endl;
	std::cout << Number::to_string(soluce) << std::endl;

	return (true);
}

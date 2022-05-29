/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:24:25 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 19:24:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cassert>
#include "Polynomial.hpp"

int
main(int argc, char **argv)
{
	{
		std::cout << "Zero" << std::endl;

		Polynomial<> polynomial = Polynomial<>::zero();

		assert(polynomial.degree() == -1);
	}

	{
		std::cout << "Constant" << std::endl;

		Polynomial<> polynomial = Polynomial<>::constant(42);

		assert(polynomial.degree() == 0);
	}

	{
		std::cout << "Linear" << std::endl;

		Polynomial<> polynomial = Polynomial<>::linear(42, 24);

		assert(polynomial.degree() == 1);
	}

	{
		std::cout << "Quadratic" << std::endl;

		Polynomial<> polynomial = Polynomial<>::quadratic(42, 24, 21);

		assert(polynomial.degree() == 2);
	}
}

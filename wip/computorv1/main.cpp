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

#include <cassert>
#include "Polynomial.hpp"
#include <set>

int
main(int argc, char **argv)
{
	Polynomial<> left = Polynomial<>::quadratic(-9.3, 4, 5);
	Polynomial<> right = Polynomial<>::constant(1);

	Polynomial<> reduced = Polynomial<>::reduce(left, right);
	std::cout << reduced << std::endl;
}

//
//	std::cout << left.degree() << std::endl;
//	std::cout << right.degree() << std::endl;
//
//	Polynomial<> reduced = Polynomial<>::reduce(left, right);
//	std::cout << reduced << std::endl;
//	std::cout << reduced.degree() << std::endl;

//	std::set<int> keys;
//	for (std::set<int>::iterator iterator = keys.begin(); iterator != keys.end(); ++iterator)
//		;

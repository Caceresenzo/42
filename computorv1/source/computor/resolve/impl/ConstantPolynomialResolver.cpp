/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConstantPolynomialResolver.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:03:10 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:03:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/resolve/impl/ConstantPolynomialResolver.hpp>
#include <iostream>

ConstantPolynomialResolver::~ConstantPolynomialResolver()
{
}

bool
ConstantPolynomialResolver::resolve(const polynomial_type &polynomial) const
{
	(void)polynomial;

	std::cout << "There is no solution" << std::endl;

	return (true);
}

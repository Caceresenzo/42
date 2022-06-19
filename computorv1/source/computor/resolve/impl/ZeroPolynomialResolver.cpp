/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZeroPolynomialResolver.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:59:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 20:59:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/resolve/impl/ZeroPolynomialResolver.hpp>
#include <iostream>

ZeroPolynomialResolver::~ZeroPolynomialResolver()
{
}

bool
ZeroPolynomialResolver::resolve(const polynomial_type &polynomial) const
{
	(void)polynomial;

	std::cout << "The solution is undefined" << std::endl;

	return (true);
}

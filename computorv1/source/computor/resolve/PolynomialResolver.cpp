/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolynomialResolver.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:56:13 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 20:56:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/Polynomial.hpp>
#include <computor/resolve/impl/ConstantPolynomialResolver.hpp>
#include <computor/resolve/impl/LinearPolynomialResolver.hpp>
#include <computor/resolve/impl/QuadraticPolynomialResolver.hpp>
#include <computor/resolve/impl/UnsupportedPolynomialResolver.hpp>
#include <computor/resolve/impl/ZeroPolynomialResolver.hpp>
#include <computor/resolve/PolynomialResolver.hpp>
#include <core/util/Singleton.hpp>

PolynomialResolver::~PolynomialResolver()
{
}

const PolynomialResolver&
PolynomialResolver::get_impl(const polynomial_type &polynomial)
{
	int degree = polynomial.degree();

	if (degree == -1)
		return (ZeroPolynomialResolver::get_instance());

	if (degree == 0)
		return (ConstantPolynomialResolver::get_instance());

	if (degree == 1)
		return (LinearPolynomialResolver::get_instance());

	if (degree == 2)
		return (QuadraticPolynomialResolver::get_instance());

	return (UnsupportedPolynomialResolver::get_instance());
}

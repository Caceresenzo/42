/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnsupportedPolynomialResolver.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:08:32 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:08:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/resolve/impl/UnsupportedPolynomialResolver.hpp>

UnsupportedPolynomialResolver::~UnsupportedPolynomialResolver()
{
}

bool
UnsupportedPolynomialResolver::resolve(const polynomial_type &polynomial) const
{
	(void)polynomial;

	std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;

	return (true);
}

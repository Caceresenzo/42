/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolynomialResolver.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:56:13 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 20:56:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYNOMIALRESOLVER_HPP_
# define POLYNOMIALRESOLVER_HPP_

#include <computor/Polynomial.hpp>

class PolynomialResolver
{
	public:
		typedef Polynomial<long double, int> polynomial_type;

	public:
		virtual
		~PolynomialResolver();

	public:
		virtual bool
		resolve(const polynomial_type &polynomial) const = 0;

	public:
		static const PolynomialResolver&
		get_impl(const polynomial_type &polynomial);
};

#endif /* POLYNOMIALRESOLVER_HPP_ */

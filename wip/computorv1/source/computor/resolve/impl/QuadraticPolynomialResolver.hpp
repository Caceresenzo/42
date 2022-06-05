/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuadraticPolynomialResolver.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:06:39 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:06:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATICPOLYNOMIALRESOLVER_HPP_
# define QUADRATICPOLYNOMIALRESOLVER_HPP_

#include <computor/resolve/PolynomialResolver.hpp>
#include <core/util/Singleton.hpp>

class QuadraticPolynomialResolver :
		public Singleton<QuadraticPolynomialResolver>,
		public PolynomialResolver
{
	public:
		virtual
		~QuadraticPolynomialResolver();

	public:
		bool
		resolve(const polynomial_type &polynomial) const;
};

#endif /* QUADRATICPOLYNOMIALRESOLVER_HPP_ */

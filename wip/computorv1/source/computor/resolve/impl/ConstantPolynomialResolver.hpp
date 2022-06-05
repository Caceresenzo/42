/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConstantPolynomialResolver.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:03:09 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:03:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTPOLYNOMIALRESOLVER_HPP_
# define CONSTANTPOLYNOMIALRESOLVER_HPP_

#include <computor/resolve/PolynomialResolver.hpp>
#include <core/util/Singleton.hpp>

class ConstantPolynomialResolver :
		public Singleton<ConstantPolynomialResolver>,
		public PolynomialResolver
{
	public:
		virtual
		~ConstantPolynomialResolver();

	public:
		bool
		resolve(const polynomial_type &polynomial) const;
};

#endif /* CONSTANTPOLYNOMIALRESOLVER_HPP_ */

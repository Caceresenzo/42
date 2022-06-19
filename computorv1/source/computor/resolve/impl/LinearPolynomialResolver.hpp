/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearPolynomialResolver.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:05:00 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:05:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEARPOLYNOMIALRESOLVER_HPP_
# define LINEARPOLYNOMIALRESOLVER_HPP_

#include <computor/resolve/PolynomialResolver.hpp>
#include <core/util/Singleton.hpp>

class LinearPolynomialResolver :
		public Singleton<LinearPolynomialResolver>,
		public PolynomialResolver
{
	public:
		virtual
		~LinearPolynomialResolver();

	public:
		bool
		resolve(const polynomial_type &polynomial) const;
};

#endif /* LINEARPOLYNOMIALRESOLVER_HPP_ */

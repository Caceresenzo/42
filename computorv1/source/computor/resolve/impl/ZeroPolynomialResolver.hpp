/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZeroPolynomialResolver.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:59:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 20:59:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZEROPOLYNOMIALRESOLVER_HPP_
# define ZEROPOLYNOMIALRESOLVER_HPP_

#include <computor/resolve/PolynomialResolver.hpp>
#include <core/util/Singleton.hpp>

class ZeroPolynomialResolver :
		public Singleton<ZeroPolynomialResolver>,
		public PolynomialResolver
{
	public:
		virtual
		~ZeroPolynomialResolver();

	public:
		bool
		resolve(const polynomial_type &polynomial) const;
};

#endif /* ZEROPOLYNOMIALRESOLVER_HPP_ */

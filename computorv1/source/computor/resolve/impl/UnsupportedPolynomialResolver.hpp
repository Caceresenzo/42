/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnsupportedPolynomialResolver.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:08:32 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:08:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSUPPORTEDPOLYNOMIALRESOLVER_HPP_
# define UNSUPPORTEDPOLYNOMIALRESOLVER_HPP_

#include <computor/resolve/PolynomialResolver.hpp>
#include <core/util/Singleton.hpp>

class UnsupportedPolynomialResolver :
		public Singleton<UnsupportedPolynomialResolver>,
		public PolynomialResolver
{
	public:
		virtual
		~UnsupportedPolynomialResolver();

	public:
		bool
		resolve(const polynomial_type &polynomial) const;
};

#endif /* UNSUPPORTEDPOLYNOMIALRESOLVER_HPP_ */

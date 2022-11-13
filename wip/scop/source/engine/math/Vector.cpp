/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 23:41:43 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/12 23:41:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/vector.hpp>

template<>
	const Vector<2, int> Vector<2, int>::ZERO(0);

template<>
	const Vector<2, float> Vector<2, float>::ZERO(0);

template<>
	const Vector<2, double> Vector<2, double>::ZERO(0);

template<>
	const Vector<3, int> Vector<3, int>::ZERO(0);

template<>
	const Vector<3, float> Vector<3, float>::ZERO(0);

template<>
	const Vector<3, float> Vector<3, float>::ONE(1);

template<>
	const Vector<3, double> Vector<3, double>::ZERO(0);

template<>
	const Vector<4, int> Vector<4, int>::ZERO(0);

template<>
	const Vector<4, float> Vector<4, float>::ZERO(0);

template<>
	const Vector<4, double> Vector<4, double>::ZERO(0);

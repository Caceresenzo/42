/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_tests.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:39:34 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 19:39:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/vector.hpp>

int
main()
{
	typedef Vector<4, float> Vector;

	{
		assert(sizeof(Vector) == sizeof(float) * 4);
	}

	{
		Vector vector;

		assert(vector.x == 0);
		assert(vector.y == 0);
		assert(vector.z == 0);
		assert(vector.w == 0);
	}

	{
		Vector vector(42, 24, 4, 2);

		assert(vector.x == 42);
		assert(vector.y == 24);
		assert(vector.z == 4);
		assert(vector.w == 2);
	}
}

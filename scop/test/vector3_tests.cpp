/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_tests.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:39:34 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 19:39:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/vector.hpp>

int
main(int argc, char **argv)
{
	typedef Vector<3, float> Vector;

	{
		assert(sizeof(Vector) == sizeof(float) * 3);
	}

	{
		Vector vector;

		assert(vector.x == 0);
		assert(vector.y == 0);
		assert(vector.z == 0);
	}

	{
		Vector vector(42, 24, 2);

		assert(vector.x == 42);
		assert(vector.y == 24);
		assert(vector.z == 2);
	}

	{
		assert(Vector() == Vector());
		assert(Vector(1, 2, 3) != Vector(4, 5, 6));
	}

	{
		assert(Vector() * 2.0f == Vector());
		assert(Vector(1, 2, 3) * 2.0f == Vector(2, 4, 6));
		assert(Vector(1, 2, 3) * -2.0f == Vector(-2, -4, -6));
	}

	{
		assert(-Vector() == Vector());
		assert(-Vector(1, 2, 3) == Vector(-1, -2, -3));
		assert(-Vector(-1, -2, -3) == Vector(1, 2, 3));
	}

	{
		assert(::cross(Vector(), Vector()) == Vector());
		assert(::cross(Vector(1, 2, 3), Vector(4, 5, 6)) == Vector(-3, 6, -3));
		assert(::cross(Vector(4, 5, 6), Vector(1, 2, 3)) == Vector(3, -6, 3));
	}

	{
		assert(::length_squared(Vector()) == 0);
		assert(::length_squared(Vector(1, 2, 3)) == 14);
		assert(::length_squared(Vector(-1, -2, -3)) == 14);
	}

	{
		assert(::normalize(Vector(0.5f, 0.5f, 0.5f)) == Vector(0.57735026, 0.57735026, 0.57735026));
		assert(::normalize(Vector(0.5, 0.5, 0.0)) == Vector(0.70710677, 0.70710677, 0));
		assert(::normalize(Vector(1.0, 0.0, 0.0)) == Vector(1.0, 0.0, 0.0));
		assert(::normalize(Vector(1, 2, 3)) == Vector(0.26726124, 0.5345225, 0.8017837));
	}

	{
		assert(::dot(Vector(), Vector()) == 0);
		assert(::dot(Vector(1, 2, 3), Vector(1, 2, 3)) == 14);
		assert(::dot(Vector(1, 2, 3), Vector(-1, -2, -3)) == -14.0);
		assert(::dot(Vector(-1, -2, -3), Vector(1, 2, 3)) == -14.0);
		assert(::dot(Vector(-1, -2, -3), Vector(-1, -2, -3)) == 14.0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3Uniform.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3UNIFORM_HPP_
# define VECTOR3UNIFORM_HPP_

#include <engine/math/vector.hpp>
#include <engine/shader/uniform/Uniform.hpp>
#include <GL/glew.h>
#include <string>

template<typename T>
	class Vector3Uniform :
			public Uniform
	{
		public:
			Vector3Uniform(const std::string &name) :
					Uniform(name)
			{
			}

		public:
			void
			set(const T &x, const T &y, const T &z);

			void
			set(const Vector3<T> &vector)
			{
				load(vector.x, vector.y, vector.z);
			}
	};

template<>
	inline void
	Vector3Uniform<float>::set(const float &x, const float &y, const float &z)
	{
		glUniform3f(location(), x, y, z);
	}

template<>
	inline void
	Vector3Uniform<double>::set(const double &x, const double &y, const double &z)
	{
		glUniform3d(location(), x, y, z);
	}

template<>
	inline void
	Vector3Uniform<int>::set(const int &x, const int &y, const int &z)
	{
		glUniform3i(location(), x, y, z);
	}

template<>
	inline void
	Vector3Uniform<unsigned>::set(const unsigned &x, const unsigned &y, const unsigned &z)
	{
		glUniform3ui(location(), x, y, z);
	}

#endif /* VECTOR3UNIFORM_HPP_ */

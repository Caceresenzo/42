/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderUniform.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:28:28 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 21:28:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/math/vector.hpp>
#include <engine/math/matrix.hpp>
#include <engine/shader/Uniform.hpp>

template<>
	void
	Uniform<bool>::set(const bool &value)
	{
		glUniform1i(location(), value);
	}

template<>
	void
	Uniform<int>::set(const int &value)
	{
		glUniform1i(location(), value);
	}

template<>
	void
	Uniform<Vector<2, int>>::set(const Vector<2, int> &value)
	{
		glUniform2i(location(), value.x, value.y);
	}

template<>
	void
	Uniform<Vector<3, float>>::set(const Vector<3, float> &value)
	{
		glUniform3f(location(), value.x, value.y, value.z);
	}

template<>
	void
	Uniform<Matrix<4, 4, float>>::set(const Matrix<4, 4, float> &value)
	{
		glUniformMatrix4fv(location(), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value[0][0]));
	}

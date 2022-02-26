/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MatrixUniform.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIXUNIFORM_HPP_
# define MATRIXUNIFORM_HPP_

#include <engine/math/matrix.hpp>
#include <engine/shader/uniform/Uniform.hpp>
#include <GL/glew.h>
#include <string>

template<typename T>
	class MatrixUniform :
			public Uniform
	{
		public:
			MatrixUniform(const std::string &name) :
					Uniform(name)
			{
			}

		public:
			void
			set(const Matrix44<T> &matrix);
	};

template<>
	inline void
	MatrixUniform<float>::set(const Matrix44<float> &matrix)
	{
		glUniformMatrix4fv(location(), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(matrix.storage));
	}

template<>
	inline void
	MatrixUniform<double>::set(const Matrix44<double> &matrix)
	{
		glUniformMatrix4dv(location(), 1, GL_FALSE, reinterpret_cast<const GLdouble*>(matrix.storage));
	}

#endif /* MATRIXUNIFORM_HPP_ */

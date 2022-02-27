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

template<int R, int C, typename T>
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
			set(const Matrix<R, C, T> &matrix);
	};

template<>
	inline void
	MatrixUniform<4, 4, float>::set(const Matrix<4, 4, float> &matrix)
	{
		glUniformMatrix4fv(location(), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&matrix[0][0]));
	}

#endif /* MATRIXUNIFORM_HPP_ */

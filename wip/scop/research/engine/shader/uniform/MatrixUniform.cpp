/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MatrixUniform.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:36:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/03 01:36:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/ShaderVariable.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>

template<>
	void
	MatrixUniform<4, 4, float>::set(const Matrix<4, 4, float> &matrix)
	{
		glUniformMatrix4fv(location(), 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&matrix[0][0]));
	}

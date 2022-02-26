/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:59:49 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:59:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERPROGRAM_HPP_
# define SHADERPROGRAM_HPP_

#include <engine/opengl.hpp>
#include <engine/shader/uniform/Uniform.hpp>
#include <GL/glew.h>
#include <string>

class ShaderProgram
{
	public:
		static const GLuint UNDEFINED_VALUE;

	private:
		GLuint m_id;

	public:
		ShaderProgram(const std::string &vertex_file, const std::string &fragment_file);

		virtual
		~ShaderProgram();

		void
		use();

		void
		unuse();

	protected:
		void
		locate(ShaderVariable &variable) const;

	public:
		GLuint
		id() const;
};

#endif /* SHADERPROGRAM_HPP_ */

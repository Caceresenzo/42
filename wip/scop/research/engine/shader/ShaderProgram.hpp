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

#include <engine/shader/uniform/Uniform.hpp>
#include <GL/glew.h>
#include <engine/opengl.hpp>
#include <string>

class ShaderProgram
{
	public:
		static const GLuint UNDEFINED_VALUE;

	private:
		GLuint m_id;

	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram &other);

		virtual
		~ShaderProgram();

		ShaderProgram&
		operator =(const ShaderProgram &other);

		void
		create(const std::string &vertex_file, const std::string &fragment_file);

		void
		use();

		void
		destroy();

		GLuint
		id() const;

	protected:
		virtual void
		after_create() = 0;

		void
		locate(Uniform &uniform) const;

	private:
		void
		compile_shader(GLuint shader_id, const std::string &path);

		void
		link_shaders(GLuint program_id, GLuint vertex_shader_id, GLuint fragment_shader_id);
};

#endif /* SHADERPROGRAM_HPP_ */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:58:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 14:58:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/exception/IllegalStateException.hpp>
#include <engine/exception/RuntimeException.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/ShaderVariable.hpp>
#include <GL/glew.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

static void
compile_shader(GLuint shader_id, const std::string &path)
{
	std::ifstream stream(path);
	std::stringstream buffer;
	buffer << stream.rdbuf();

	std::cout << path << ": compiling" << std::endl << std::flush;

	std::string code = buffer.str();
	const char *code_raw = code.c_str();

	glShaderSource(shader_id, 1, &code_raw, NULL);
	glCompileShader(shader_id);

	GLint result = GL_FALSE;
	GLint info_log_length = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length > 0)
	{
		printf("%d\n", info_log_length);

		char err[info_log_length + 1];
		std::memset(err, '?', info_log_length);
		glGetShaderInfoLog(shader_id, info_log_length, NULL, err);
		err[info_log_length] = '\0';
		write(1, err, info_log_length);

		if (!result)
			throw RuntimeException(std::string("could not compile: ") + err);
	}
}

static void
link_shaders(GLuint program_id, GLuint vertex_shader_id, GLuint fragment_shader_id)
{
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	GLint result = GL_FALSE;
	GLint info_log_length;
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if (info_log_length > 0)
	{
		char err[info_log_length + 1];
		std::memset(err, 0, info_log_length);
		glGetProgramInfoLog(program_id, info_log_length, NULL, err);
		err[info_log_length] = '\0';

		throw RuntimeException(err);
	}
}

const GLuint ShaderProgram::UNDEFINED_VALUE = GLuint(-1);

ShaderProgram::ShaderProgram(const std::string &vertex_file, const std::string &fragment_file)
{
	GLuint vertex_shader_id = -1;
	GLuint fragment_shader_id = -1;
	GLuint program_id = -1;

	try
	{
		vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
		compile_shader(vertex_shader_id, vertex_file);

		fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		compile_shader(fragment_shader_id, fragment_file);

		program_id = glCreateProgram();
		link_shaders(program_id, vertex_shader_id, fragment_shader_id);

		glDetachShader(program_id, vertex_shader_id);
		glDetachShader(program_id, fragment_shader_id);

		glDeleteShader(vertex_shader_id);
		vertex_shader_id = -1;

		glDeleteShader(fragment_shader_id);
		fragment_shader_id = -1;

		this->m_id = program_id;
	}
	catch (...)
	{
		if (vertex_shader_id != UNDEFINED_VALUE)
			glDeleteProgram(vertex_shader_id);

		if (fragment_shader_id != UNDEFINED_VALUE)
			glDeleteShader(fragment_shader_id);

		if (program_id != UNDEFINED_VALUE)
			glDeleteProgram(program_id);

		throw;
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

void
ShaderProgram::use()
{
	glUseProgram(m_id);
}

void
ShaderProgram::unuse()
{
	glUseProgram(0);
}

void
ShaderProgram::locate(ShaderVariable &variable) const
{
	variable.locate(*this);
}

GLuint
ShaderProgram::id() const
{
	return (m_id);
}

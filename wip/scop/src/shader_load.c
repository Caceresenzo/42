/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:24:49 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 14:24:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shader.h"

static bool
shader_compile_source(GLint id, const char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);

	char buff[4096];

	int size = read(fd, buff, sizeof(buff));
	if (size == -1)
	{
		close(fd);
		return (false);
	}

	buff[size] = '\0';
	close(fd);

	const char *buffer = buff;
	// Compile Vertex Shader
	printf("%s: compiling\n", file);
	glShaderSource(id, 1, &buffer, NULL);
	glCompileShader(id);

	return (shader_error(id, file, false));
}

static bool shader_program_link(t_shader *shader)
{
	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vertex);
	glAttachShader(shader->program, shader->fragment);
	glLinkProgram(shader->program);

	return (shader_error(shader->program, "linking", true));
}

bool
shader_load_at(t_shader *shader, const char *vertex_file, const char *fragment_file)
{
	shader->vertex = glCreateShader(GL_VERTEX_SHADER);
	shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

	shader_compile_source(shader->vertex, vertex_file);
	shader_compile_source(shader->fragment, fragment_file);
	shader_program_link(shader);

	glDetachShader(shader->program, shader->vertex);
	glDetachShader(shader->program, shader->fragment);

	glDeleteShader(shader->vertex);
	glDeleteShader(shader->fragment);

	return (true);
}

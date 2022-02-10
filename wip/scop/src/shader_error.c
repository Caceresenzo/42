/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:30:56 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 14:30:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "shader.h"

bool
shader_error(GLuint id, const char *name, bool is_program)
{
	GLint result = GL_FALSE;
	int info_log_length;

	if (is_program)
	{
		glGetProgramiv(id, GL_LINK_STATUS, &result);
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
	}
	else
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
	}

	if (info_log_length > 0)
	{
		char err[info_log_length + 1];
		bzero(err, info_log_length + 1);

		if (is_program)
			glGetProgramInfoLog(id, info_log_length, NULL, err);
		else
			glGetShaderInfoLog(id, info_log_length, NULL, err);

		err[info_log_length] = '\0';

		printf("%s: %s\n", name, err);

		return (false);
	}

	return (result);
}

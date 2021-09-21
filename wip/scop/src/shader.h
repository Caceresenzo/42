/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:20:50 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 14:20:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

# include <stdbool.h>
# include "opengl.h"

typedef struct s_shader
{
	GLuint vertex;
	GLuint fragment;
	GLuint program;
} t_shader;

bool
shader_load_at(t_shader *shader, const char *vertex_file, const char *fragment_file);

bool
shader_error(GLuint id, const char *name, bool is_program);

#endif

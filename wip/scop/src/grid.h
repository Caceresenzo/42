/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:24:06 by ecaceres          #+#    #+#             */
/*   Updated: 2021/11/25 17:24:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

# include <stdbool.h>

# include "opengl.h"
# include "shader.h"
# include "vector.h"
# include "arraylist.h"

typedef struct s_grid_params
{
	int slices;
	t_shader *shader;
} t_grid_params;

typedef struct s_grid
{
	GLuint vertex_array_object;
	GLuint vertex_buffer_object;
	GLuint indice_buffer_object;
	GLuint length;
	t_arraylist vertices;
	t_arraylist indices;
	t_grid_params params;
} t_grid;

bool
grid_initialize(t_grid *grid, t_grid_params params);

void
grid_draw(t_grid *grid);

void
grid_destroy(t_grid *grid);

#endif

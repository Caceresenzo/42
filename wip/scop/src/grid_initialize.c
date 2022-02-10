/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:29:11 by ecaceres          #+#    #+#             */
/*   Updated: 2021/11/25 17:29:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "grid.h"

bool
grid_initialize(t_grid *grid, t_grid_params params)
{
	if (!grid)
		return (false);

	memcpy(&grid->params, &params, sizeof(t_grid_params));

	if (!arraylist_initialize(&grid->vertices, 0, sizeof(t_v3f)))
		return (false);

	if (!arraylist_initialize(&grid->indices, 0, sizeof(t_v4u)))
	{
		arraylist_destroy(&grid->vertices);
		return (false);
	}

	for (int j = 0; j <= params.slices; ++j)
	{
		for (int i = 0; i <= params.slices; ++i)
		{
			float x = (float)i / (float)params.slices;
			float y = 0;
			float z = (float)j / (float)params.slices;

			t_v3f v3 = { x, y, z };

			t_v3f *to = arraylist_add_to(&grid->vertices);

			if (!to)
			{
				arraylist_destroy(&grid->vertices);
				arraylist_destroy(&grid->indices);
				return (false);
			}

			memcpy(to, &v3, sizeof(t_v3f));
		}
	}

	for (int j = 0; j < params.slices; ++j)
	{
		for (int i = 0; i < params.slices; ++i)
		{

			int row1 = j * (params.slices + 1);
			int row2 = (j + 1) * (params.slices + 1);

			t_v4u v4_1 = { row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1 };
			t_v4u v4_2 = { row2 + i + 1, row2 + i, row2 + i, row1 + i };

			t_v4u *to1 = arraylist_add_to(&grid->indices);
			t_v4u *to2 = arraylist_add_to(&grid->indices);

			if (!to1 || !to2)
			{
				arraylist_destroy(&grid->vertices);
				arraylist_destroy(&grid->indices);
				return (false);
			}

			memcpy(to1, &v4_1, sizeof(t_v4u));
			memcpy(to2, &v4_2, sizeof(t_v4u));
		}
	}

	glGenVertexArrays(1, &grid->vertex_array_object);
	glBindVertexArray(grid->vertex_array_object);

	glGenBuffers(1, &grid->vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, grid->vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, grid->vertices.size * sizeof(t_v3f), grid->vertices.vector, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &grid->indice_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid->indice_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, grid->indices.size * sizeof(t_v4u), grid->indices.vector, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);

	grid->length = (GLuint)grid->indices.size * 4;

	glBindVertexArray(0);

	return (true);
}

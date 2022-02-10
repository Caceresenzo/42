/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:39:51 by ecaceres          #+#    #+#             */
/*   Updated: 2021/11/25 17:39:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "grid.h"

void
grid_draw(t_grid *grid)
{
	if (!grid)
		return;

	t_m4f model;
	m4f_identity(&model);

	t_v3f translate = { -(grid->params.slices), 0.0f, -(grid->params.slices) };
	m4f_translate_v3(&model, &translate);

	t_v3f scale = { 20.0f, 20.0f, 20.0f };
	m4f_scale_v3(&model, &scale);

	GLint id = glGetUniformLocation(grid->params.shader->program, "m");
	glUniformMatrix4fv(id, 1, GL_FALSE, &model.m[0][0]);

	glBindVertexArray(grid->vertex_array_object);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_LINES, grid->length, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

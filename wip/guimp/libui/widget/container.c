/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "container.h"

static t_ui_widget_descriptor container_descriptor = {
	.name = "container",
	.size = sizeof(t_ui_container),
	.handlers = {
		.draw = {
			.code = (void*)&ui_container_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_container_size,
			.data = NULL
		},
	}
};

t_ui_container*
ui_container_new(t_ui_container_direction direction)
{
	t_ui_container *container = cast(ui_widget_new(&container_descriptor));
	container->direction = direction;

	return (container);
}

void
ui_container_size(t_ui_container *container, void *data)
{
	if (container->direction == UI_CONTAINER_DIRECTION_VERTICAL)
		ui_group_size_widget(cast(container), UI_GROUP_DIRECTION_VERTICAL);
	else if (container->direction == UI_CONTAINER_DIRECTION_HORIZONTAL)
		ui_group_size_widget(cast(container), UI_GROUP_DIRECTION_HORIZONTAL);
	ui_style_apply_size(cast(container));
	(void)data;
}

void
ui_container_draw(t_ui_container *container, void *data)
{
//	if (container->color == 0)
//		container->color = SDL_MapRGB(container->super._surface->format, rand() % 255, rand() % 255, rand() % 255);
//	SDL_FillRect(container->super._surface, NULL, container->color);

	ui_group_draw_widget(cast(container));
	(void)data;
}

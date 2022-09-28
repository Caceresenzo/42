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
	.size = sizeof(t_ui_container)
};

t_ui_container*
ui_container_new(t_ui_container_direction direction)
{
	t_ui_container *container = cast(ui_widget_new(&container_descriptor));
	container->super.size_handler.function = cast(&ui_container_size);
	container->super.draw_handler.function = cast(&ui_container_draw);
	container->direction = direction;

	return (container);
}

void
ui_container_size(t_ui_container *container, void *data)
{
	t_list_node *node;
	t_ui_widget *widget;
	int x = 0;
	int y = 0;

	node = container->super.children.first;
	while (node)
	{
		widget = node->data;
		ui_widget_size(widget);
		if (container->direction == CONTAINER_DIRECTION_VERTICAL)
		{
			widget->position.y = y;
			y += widget->size.y;
			x = MAX(widget->size.x, x);
		} else {
			widget->position.x = x;
			x += widget->size.x;
			y = MAX(widget->size.y, y);
		}
		node = node->next;
	}
	container->super.size.x = x;
	container->super.size.y = y;
	(void)data;
}

void
ui_container_draw(t_ui_container *container, void *data)
{
	t_list_node *node;
	SDL_LockSurface(container->super._surface);
	SDL_FillRect(container->super._surface, NULL, SDL_MapRGB(container->super._surface->format, 255, 0, 0));
	SDL_UnlockSurface(container->super._surface);

	node = container->super.children.first;
	while (node)
	{
		ui_widget_draw(node->data);
		node = node->next;
	}
	(void)data;
}

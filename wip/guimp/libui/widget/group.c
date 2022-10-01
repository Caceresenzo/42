/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 00:32:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 00:32:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group.h"

static void
impl_vertical(t_ui_widget *widget, t_vector2i *size)
{
	widget->position.x = 0;
	widget->position.y = size->y;
	size->x = MAX(widget->size.x, size->x);
	size->y += widget->size.y;
}

static void
impl_horizontal(t_ui_widget *widget, t_vector2i *size)
{
	widget->position.x = size->x;
	widget->position.y = 0;
	size->x += widget->size.x;
	size->y = MAX(widget->size.y, size->y);
}

t_vector2i
ui_group_size(t_list *children, t_ui_group_direction direction)
{
	t_vector2i size;
	t_list_node *node;
	t_ui_widget *widget;

	size = vector2i_zero();
	node = children->first;
	while (node)
	{
		widget = node->data;
//		printf("group sizing widget = (%p aka %s (children: %ld)\n", widget, widget->descriptor->name, widget->children.size);
		ui_widget_size(widget);
		if (direction == UI_GROUP_DIRECTION_VERTICAL)
			impl_vertical(widget, &size);
		else if (direction == UI_GROUP_DIRECTION_HORIZONTAL)
			impl_horizontal(widget, &size);
		node = node->next;
	}
	return (size);
}

void
ui_group_size_widget(t_ui_widget *widget, t_ui_group_direction direction)
{
	widget->size = ui_group_size(&widget->children, direction);
}

void
ui_group_draw(t_list *children)
{
	t_list_node *node;

	node = children->first;
	while (node)
	{
		ui_widget_draw(node->data);
		node = node->next;
	}
}

void
ui_group_draw_widget(t_ui_widget *widget)
{
	ui_group_draw(&widget->children);
}

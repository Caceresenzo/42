/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:59:47 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:59:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void
ui_widget_dump_impl(t_ui_widget *widget, int depth)
{
	t_list_node *node;

	printf("%*s%s (position=%dx%d, size=%dx%d, dirty=%d)\n", depth * 2, "", widget->descriptor->name, widget->position.x, widget->position.y, widget->size.x, widget->size.y, widget->dirty);

	node = widget->children.first;
	while (node)
	{
		ui_widget_dump_impl(node->data, depth + 1);
		node = node->next;
	}
}

static void
ui_window_dump_impl(t_ui_window *window, int depth)
{
	printf("%*swindow: `%s` (size=%dx%d)\n", depth * 2, "", ui_window_get_title(window), window->size.x, window->size.y);
	if (window->root)
		ui_widget_dump_impl(window->root, depth + 1);
}

void
ui_application_dump(t_ui_application *app)
{
	t_list_node *node;

	printf("application: `%s`\n", app->name);

	node = app->windows.first;
	while (node)
	{
		ui_window_dump_impl(node->data, 1);
		node = node->next;
	}
}

void
ui_window_dump(t_ui_window *window)
{
	ui_window_dump_impl(window, 0);
}

void
ui_widget_dump(t_ui_widget *widget)
{
	ui_widget_dump_impl(widget, 0);
}

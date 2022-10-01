/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:24:51 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:24:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

t_ui_window*
ui_window_new(t_ui_application *app, t_vector2i position, t_vector2i size, uint32_t flags)
{
	t_ui_window *window = calloc(sizeof(t_ui_window), 1);
	if (!window)
		return (NULL);

	window->size = size;
	window->app = app;
	list_add(&app->windows, window);

	window->_window = SDL_CreateWindow(
		"libui",
		position.x, position.y,
		size.x, size.y,
		flags
		);

	if (!window->_window)
		sdl_abort("SDL_Window");

	return (window);
}

void
ui_window_destroy(t_ui_window *window)
{
	if (!list_remove(&window->app->windows, window, NULL))
		printf("warning: not removed from windows list\n");

	SDL_DestroyWindow(window->_window);
	free(window);
}

const char*
ui_window_get_title(t_ui_window *window)
{
	return (SDL_GetWindowTitle(window->_window));
}

void
ui_window_set_title(t_ui_window *window, const char *title)
{
	SDL_SetWindowTitle(window->_window, title);
}

static void
ui_widget_set_window_resursive(t_ui_widget *widget, t_ui_window *window)
{
	t_list_node *node;

	widget->window = window;
	node = widget->children.first;
	while (node)
	{
		ui_widget_set_window_resursive(node->data, window);
		node = node->next;
	}
}

t_ui_widget*
ui_window_set_root(t_ui_window *window, t_ui_widget *widget)
{
	t_ui_widget *old = window->root;

	window->root = widget;
	window->dirty = true;

	widget->position.x = 0;
	widget->position.y = 0;

	widget->size = window->size;

	ui_widget_set_window_resursive(widget, window);

	return (old);
}

void
ui_widget_add(t_ui_widget *parent, t_ui_widget *widget)
{
	list_add(&parent->children, widget);
	widget->parent = parent;
	widget->window = parent->window;
	parent->dirty = true;
}

void
ui_window_draw(t_ui_window *window)
{
	if (!window->dirty || !window->root)
		return;
	window->dirty = false;

	ui_widget_size(window->root);
	ui_widget_draw(window->root);

	SDL_Surface *surface = SDL_GetWindowSurface(window->_window);
//	SDL_LockSurface(surface);

	if (SDL_BlitSurface(window->root->_surface, NULL, surface, NULL))
		sdl_abort("SDL_BlitSurface");

//	SDL_UnlockSurface(surface);
	SDL_UpdateWindowSurface(window->_window);

//	ui_window_dump(window);
}

typedef int
(*t_ui_event_mouse_consumer)(t_ui_widget*, const t_ui_event_mouse*);

int
hitscan_at(t_ui_widget *widget, const t_ui_event_base *event, t_vector2i point)
{
	t_list_node *node;
	t_ui_widget *child;
	int response = UI_EVENT_CONTINUE;

	response = ui_widget_event_call(widget, event);
	if (response != UI_EVENT_CONTINUE)
		return (response);

	node = widget->children.first;
	while (node)
	{
		child = node->data;
//		printf("%d <= %d (%d) && %d <= %d (%d)\n", widget->size.x, x, widget->size.x <= x, widget->size.y, y, widget->size.y <= y);
		if (ui_widget_is_inside(child, point))
		{
//			printf("%p :: %s\n", child, child->descriptor->name);
			response = hitscan_at(child, event, vector2i_substract(point, child->position));
			break;
		}
		node = node->next;
	}

	return (response);
}

void
hitscan(const t_ui_event_base *event, t_vector2i point)
{
	t_ui_window *window = event->window;

//	printf("\n\nhitscan_at\n");
	hitscan_at(window->root, event, point);
}

void
ui_window_dispatch_mouse(const t_ui_event_mouse *event)
{
	hitscan(ccast(event), event->position);
}

void
ui_window_dispatch(const t_ui_event_base *base_event)
{
	if (base_event->type == UI_EVENT_TYPE_MOUSE_MOTION
		|| base_event->type == UI_EVENT_TYPE_MOUSE_PRESSED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_RELEASED)
	{
		ui_window_dispatch_mouse(ccast(base_event));
	}
}

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

t_ui_widget*
hitscan(t_ui_widget *widget, t_vector2i point)
{
	t_list_node *node;
	t_ui_widget *child;

	if (!widget->traversable)
		return (widget);

	node = widget->children.first;
	while (node)
	{
		child = node->data;
		if (ui_widget_is_inside(child, point))
		{
			printf("%p :: %s\n", child, child->descriptor->name);
			return (hitscan(child, vector2i_substract(point, child->position)));
		}
		node = node->next;
	}

	return (widget);
}

//void
//hitscan(const t_ui_event_base *event, t_vector2i point)
//{
//	t_ui_window *window = event->window;
//
//	printf("\n\nhitscan_at\n");
//	t_ui_widget* widget = hitscan_at(window->root, event, point);
//	if (widget)
//		ui_widget_event_call(widget, event);
//}

void
ui_window_dispatch_mouse(const t_ui_event_mouse *event)
{
	t_ui_window *window = event->super.window;

	printf("\n\nui_window_dispatch_mouse\n");
	t_ui_widget *widget = hitscan(window->root, vector2i(event->x, event->y));
	if (window->focused && widget != window->focused)
	{
		t_ui_event_mouse event2 = *event;
		event2.super.type = UI_EVENT_TYPE_MOUSE_EXITED;

		ui_widget_event_call(window->focused, cast(&event2));
		window->focused = NULL;
	}

	if (widget && !window->focused)
	{
		t_ui_event_mouse event2 = *event;
		event2.super.type = UI_EVENT_TYPE_MOUSE_ENTERED;

		window->focused = widget;
		ui_widget_event_call(window->focused, cast(&event2));
	}

	ui_widget_event_call(widget, ccast(event));

	if (widget && widget->focusable)
	{
		if (event->super.type == UI_EVENT_TYPE_MOUSE_PRESSED)
			window->focused = widget;

		if (event->super.type == UI_EVENT_TYPE_MOUSE_RELEASED && window->focused == widget)
		{
			t_ui_event_mouse event2 = *event;
			event2.super.type = UI_EVENT_TYPE_MOUSE_CLICKED;

			ui_widget_event_call(widget, cast(&event2));
		}
	}
}

void
ui_window_dispatch(const t_ui_event_base *base_event)
{
	if (base_event->type == UI_EVENT_TYPE_MOUSE_MOVED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_DRAGGED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_CLICKED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_ENTERED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_EXITED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_PRESSED
		|| base_event->type == UI_EVENT_TYPE_MOUSE_RELEASED)
	{
		ui_window_dispatch_mouse(ccast(base_event));
	}
}

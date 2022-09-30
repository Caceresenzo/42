/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:25:33 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:25:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widget.h"

t_ui_widget*
ui_widget_new(t_ui_widget_descriptor *descriptor)
{
	t_ui_widget *widget;

	widget = calloc(descriptor->size, 1);
	if (!widget)
		return (NULL);
	widget->descriptor = descriptor;
	widget->dirty = true;
	return (widget);
}

static bool
ui_widget_is_new_surface_needed(t_ui_widget *widget)
{
	SDL_Surface *surface;

	surface = widget->_surface;
	if (!surface)
		return (true);

	return (surface->w != widget->size.x || surface->h != widget->size.y);
}

void
ui_widget_size(t_ui_widget *widget)
{
	ui_widget_size_call(widget);
}

void
ui_widget_draw(t_ui_widget *widget)
{
	if (ui_widget_is_new_surface_needed(widget))
	{
		if (widget->_surface)
			SDL_FreeSurface(widget->_surface);
		widget->_surface = SDL_CreateRGBSurface(0, widget->size.x, widget->size.y, 32, 0, 0, 0, 0);
		printf("allocated surface: %p\n", widget->_surface);
	}

	ui_widget_draw_call(widget);

	if (widget->parent)
	{
		SDL_Rect srcrect = { 0, 0, widget->size.x, widget->size.y };
		SDL_Rect dstrect = { widget->position.x, widget->position.y, widget->size.x, widget->size.y };
		if (SDL_BlitSurface(widget->_surface, &srcrect, widget->parent->_surface, &dstrect))
			sdl_abort("SDL_BlitSurface");
	}
}

void
ui_widget_set_dirty(t_ui_widget *widget)
{
	widget->dirty = true;

	// TODO Mark tree as dirty
	if (widget->window)
		widget->window->dirty = true;
}

bool
ui_widget_is_inside(t_ui_widget *widget, t_vector2i point)
{
//	printf("widget(%s, %d, %d, %d, %d), point(%d, %d) - %d %d %d %d\n",
//		widget->descriptor->name, widget->position.x, widget->position.y, widget->size.x, widget->size.y,
//		point.x, point.y,
//		point.x >= widget->position.x,
//		point.y >= widget->position.y,
//		widget->position.x + widget->size.x >= point.x,
//		widget->position.y + widget->size.y >= point.y
//			);
	return (point.x >= widget->position.x
		&& point.y >= widget->position.y
		&& widget->position.x + widget->size.x >= point.x
		&& widget->position.y + widget->size.y >= point.y);
}

static void
ui_widget_function_call(t_ui_widget *widget, t_ui_widget_function *function)
{
	if (function->code)
		function->code(widget, function->data);
}

void
ui_widget_draw_call(t_ui_widget *widget)
{
	ui_widget_function_call(widget, &widget->descriptor->handlers.draw);
}

void
ui_widget_size_call(t_ui_widget *widget)
{
	ui_widget_function_call(widget, &widget->descriptor->handlers.size);
}

int
ui_widget_event_call(t_ui_widget *widget, const t_ui_event_base *event)
{
	t_ui_widget_function_event *function;

	function = &widget->descriptor->handlers.event;
	if (function->code)
		return (function->code(widget, event, function->data));
	return (UI_EVENT_CONTINUE);
}

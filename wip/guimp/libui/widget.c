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
	t_ui_widget *widget = calloc(descriptor->size, 1);
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
	ui_callback_size_call(widget);
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

	ui_callback_draw_call(widget);

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

	// TODO
//	assert(widget->window);
//	widget->window->dirty = true;
}

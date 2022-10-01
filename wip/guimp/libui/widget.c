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

#include "ui.h"

t_ui_widget*
ui_widget_new(t_ui_widget_descriptor *descriptor)
{
	t_ui_widget *widget;

	widget = calloc(descriptor->size, 1);
	if (!widget)
		return (NULL);
	widget->descriptor = descriptor;
	widget->dirty = true;
	widget->focusable = true;
	widget->traversable = true;
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
//	printf("ui_widget_size(%p aka %s (children: %ld)\n", widget, widget->descriptor->name, widget->children.size);
	ui_widget_size_call(widget);
}

void
ui_widget_draw(t_ui_widget *widget)
{
	if (ui_widget_is_new_surface_needed(widget))
	{
		if (widget->_surface)
			SDL_FreeSurface(widget->_surface);
		widget->_surface = SDL_CreateRGBSurface(0, widget->size.x, widget->size.y, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
//		SDL_FillRect(widget->_surface, NULL, SDL_MapRGBA(widget->_surface->format, 255, 0, 0, 80));
//		SDL_SetSurfaceBlendMode(widget->_surface, SDL_BLENDMODE_NONE);
//		SDL_SetSurfaceAlphaMod(widget->_surface, SDL_ALPHA_TRANSPARENT);
		printf("allocated surface: %p\n", widget->_surface);
	}

	if (widget->style.background_color.present)
		SDL_FillRect(widget->_surface, NULL, widget->style.background_color.value);
	else
		SDL_FillRect(widget->_surface, NULL, 0x00000000);

	ui_widget_draw_call(widget);

	if (widget->parent)
	{
		SDL_Rect srcrect = { 0, 0, widget->size.x, widget->size.y };
		SDL_Rect dstrect = { widget->position.x, widget->position.y, widget->size.x, widget->size.y };
//		SDL_BlendMode mode;
//		SDL_GetSurfaceBlendMode(widget->_surface, &mode);
//		SDL_SetSurfaceBlendMode(widget->_surface, SDL_BLENDMODE_BLEND);
		if (SDL_BlitSurface(widget->_surface, &srcrect, widget->parent->_surface, &dstrect))
			sdl_abort("SDL_BlitSurface");
//		SDL_SetSurfaceBlendMode(widget->_surface, mode);
	}
}

void
ui_widget_set_id(t_ui_widget *widget, const char *id)
{
	free(widget->id);
	if (id)
		widget->id = strdup(id);
	else
		widget->id = NULL;
}

void
ui_widget_set_dirty(t_ui_widget *widget)
{
	widget->dirty = true;

	// TODO Mark tree as dirty
	if (widget->window)
		widget->window->dirty = true;
}

t_ui_widget*
ui_widget_find_by_id(t_ui_widget *widget, const char *id)
{
	t_list_node *node;
	t_ui_widget *found;

	if (!id)
		return (NULL);
	if (widget->id && !strcmp(widget->id, id))
		return (widget);
	node = widget->children.first;
	while (node)
	{
		found = ui_widget_find_by_id(node->data, id);
		if (found)
			return (found);
		node = node->next;
	}

	return (NULL);
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

void
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

void
ui_widget_event_call(t_ui_widget *widget, const t_ui_event_base *event)
{
	t_ui_widget_function_event *function;

	function = &widget->descriptor->handlers.event;
	if (function->code)
		function->code(widget, event, function->data);
}

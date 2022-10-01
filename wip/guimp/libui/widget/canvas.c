/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:39:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 23:39:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

static t_ui_widget_descriptor canvas_descriptor = {
	.name = "canvas",
	.size = sizeof(t_ui_canvas),
	.handlers = {
		.draw = {
			.code = (void*)&ui_canvas_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_canvas_size,
			.data = NULL
		},
		.event = {
			.code = (void*)&ui_canvas_event,
			.data = NULL
		}
	}
};

t_ui_canvas*
ui_canvas_new(t_vector2i dimension)
{
	t_ui_canvas *canvas;

	canvas = cast(ui_widget_new(&canvas_descriptor));
	canvas->super.traversable = false;
	canvas->super.focusable = false;

	canvas->surface = SDL_CreateRGBSurface(0, dimension.x, dimension.y, 32, 0xff0000, 0xff00, 0xff, 0xff000000);
	SDL_FillRect(canvas->surface, NULL, 0xff535353);
	canvas->dimension = dimension;

	return (canvas);
}

void
ui_canvas_set_pixel(t_ui_canvas *canvas, t_vector2i position, int color)
{
	Uint32 *pixels = canvas->surface->pixels;
	pixels[position.y * canvas->dimension.x + position.x] = color;
	ui_widget_set_dirty(cast(canvas));
}

void
ui_canvas_size(t_ui_canvas *canvas, void *data)
{
	canvas->super.size = canvas->dimension;
	ui_style_apply_size(cast(canvas));
	(void)data;
}

void
ui_canvas_draw(t_ui_canvas *canvas, void *data)
{
	SDL_Rect srcrec = { 0, 0, canvas->surface->w, canvas->surface->h };
	SDL_Rect destrec = { 0, 0, canvas->super.size.x, canvas->super.size.y };
	SDL_BlitScaled(canvas->surface, &srcrec, canvas->super._surface, &destrec);
	(void)data;
}

void
ui_canvas_event(t_ui_canvas *canvas, t_ui_event_base *event, void *data)
{
	t_ui_event_mouse *mouse_event = cast(event);

	int color = 0;
	if (event->type == UI_EVENT_TYPE_MOUSE_MOVED)
		color = 0xffffffff;
	else if (event->type == UI_EVENT_TYPE_MOUSE_DRAGGED)
		color = 0xff00ffff;

	if (color)
	{
		printf("color=%x x=%d y=%d\n", color, mouse_event->local.x, mouse_event->local.y);
		ui_canvas_set_pixel(canvas, mouse_event->local, color);
	}

	(void)data;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewport.h"

static t_ui_widget_descriptor viewport_descriptor = {
	.name = "viewport",
	.size = sizeof(t_ui_viewport),
	.children_limit = 1,
	.handlers = {
		.describe = {
			.code = (void*)&ui_viewport_describe,
			.data = NULL
		},
		.hitscan_interceptor = {
			.code = (void*)&ui_viewport_hitscan_interceptor,
			.data = NULL
		},
		.draw = {
			.code = (void*)&ui_viewport_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_viewport_size,
			.data = NULL
		},
	}
};

t_ui_viewport*
ui_viewport_new(void)
{
	t_ui_viewport *viewport = cast(ui_widget_new(&viewport_descriptor));
	return (viewport);
}

bool
ui_viewport_set_offset(t_ui_viewport *this, t_vector2i offset)
{
	if (!vector2i_equals(this->offset, offset))
	{
		this->offset = offset;
		ui_widget_set_dirty(cast(this));
		return (true);
	}
	return (false);
}

void
ui_viewport_size(t_ui_viewport *viewport, void *data)
{
	ui_group_size(&viewport->super.children, UI_GROUP_DIRECTION_NONE);
	ui_style_apply_size(cast(viewport));

	(void)data;
}

void
ui_viewport_describe(t_ui_viewport *this, char *buffer, void *data)
{
	sprintf(buffer, "offset={%d,%d}", this->offset.x, this->offset.y);
}

void
ui_viewport_hitscan_interceptor(t_ui_viewport *viewport, t_vector2i *point, void *data)
{
	t_ui_widget *first = ui_widget_get_child(cast(viewport), 0);

	if (!first)
		return;

	*point = vector2i_add(*point, viewport->offset);
}

void
ui_viewport_draw(t_ui_viewport *viewport, void *data)
{
	ui_group_draw_widget(cast(viewport), false);

	t_ui_widget *first = ui_widget_get_child(cast(viewport), 0);
	if (!first)
		return;

	SDL_Rect srcrect = {
		viewport->offset.x,
		viewport->offset.y,
		viewport->super.size.x,
		viewport->super.size.y
	};
	SDL_Rect dstrect = { 0, 0, viewport->super.size.x, viewport->super.size.y };
	if (SDL_BlitSurface(first->_surface, &srcrect, viewport->super._surface, &dstrect))
		sdl_abort("SDL_BlitSurface");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scroll.h"

static t_ui_widget_descriptor scroll_descriptor = {
	.name = "scroll",
	.size = sizeof(t_ui_scroll),
	.children_limit = 1,
	.handlers = {
		.draw = {
			.code = (void*)&ui_scroll_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_scroll_size,
			.data = NULL
		},
		.event = {
			.code = (void*)&ui_scroll_event,
			.data = NULL
		},
	}
};

t_ui_scroll*
ui_scroll_new(void)
{
	t_ui_scroll *scroll = cast(ui_widget_new(&scroll_descriptor));
	scroll->vertical.policy = UI_SCROLLBAR_POLICY_ALWAYS;

	return (scroll);
}

void
ui_scroll_size(t_ui_scroll *scroll, void *data)
{
	ui_group_size_widget(cast(scroll), UI_GROUP_DIRECTION_VERTICAL);
	ui_style_apply_size(cast(scroll));
	(void)data;
}

t_ui_widget*
ui_widget_get_child(t_ui_widget *widget, int index)
{
	t_list_node *node;

	node = widget->children.first;
	while (node)
	{
		if (index-- == 0)
			return (node->data);
		node = node->next;
	}
	return (NULL);
}

void
ui_scroll_draw(t_ui_scroll *scroll, void *data)
{
	ui_group_draw_widget(cast(scroll), false);

	t_ui_widget *first = ui_widget_get_child(cast(scroll), 0);
	if (!first)
		return;

	SDL_Rect srcrect = { 0, scroll->vertical.offset, scroll->super.size.x, scroll->super.size.y };
	SDL_Rect dstrect = { 0, 0, scroll->super.size.x, scroll->super.size.y };
	if (SDL_BlitSurface(first->_surface, &srcrect, scroll->super._surface, &dstrect))
		sdl_abort("SDL_BlitSurface");
}

#define CLAMP(x,lo,hi) MIN((hi), MAX((lo), (x)))

void
ui_scroll_event(t_ui_scroll *scroll, t_ui_event_base *event, void *data)
{
	if (event->type != UI_EVENT_TYPE_MOUSE_WHEEL_MOVED)
		return;

	t_ui_event_mouse_wheel *wheel_event = cast(event);
	t_ui_widget *first = ui_widget_get_child(cast(scroll), 0);

	if (wheel_event->scroll.y)
	{
		int offset = scroll->vertical.offset - wheel_event->scroll.y * 10;
		int max = first ? MAX(first->size.y - scroll->super.size.y, 0) : 0;
		scroll->vertical.offset = CLAMP(offset, 0, max);
	}

	printf("offset v%d\n", scroll->vertical.offset);

	ui_widget_set_dirty(cast(scroll));
}

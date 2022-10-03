/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
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
	.children_limit = 0,
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

# define VERTICAL_SCROLLBAR_INDEX (0)
# define HORIZONTAL_SCROLLBAR_INDEX (VERTICAL_SCROLLBAR_INDEX + 1)
# define CHILD_INDEX (HORIZONTAL_SCROLLBAR_INDEX + 1)

t_ui_scroll*
ui_scroll_new(void)
{
	t_ui_scroll *scroll = cast(ui_widget_new(&scroll_descriptor));

	scroll->viewport = ui_viewport_new();
	scroll->viewport->super.managed = true;

	scroll->vertical = ui_scrollbar_new(UI_SCROLLBAR_ORIENTATION_VERTICAL);
	scroll->vertical->super.managed = true;

	scroll->horizontal = ui_scrollbar_new(UI_SCROLLBAR_ORIENTATION_HORIZONTAL);
	scroll->horizontal->super.managed = true;

	ui_widget_add(cast(scroll), cast(scroll->viewport));
	ui_widget_add(cast(scroll), cast(scroll->vertical));
	ui_widget_add(cast(scroll), cast(scroll->horizontal));

	return (scroll);
}

void
ui_scroll_size(t_ui_scroll *this, void *data)
{
	ui_widget_size(cast(this->viewport));
	ui_widget_size(cast(this->horizontal));
	ui_widget_size(cast(this->vertical));
	ui_style_apply_size(cast(this));

	this->viewport->super.size = this->super.size;

	this->horizontal->super.size.x = this->super.size.x;
	this->vertical->super.size.y = this->super.size.y;

	if (this->vertical->visible && this->horizontal->visible)
	{
		this->horizontal->super.size.x -= this->vertical->super.size.x;
		this->vertical->super.size.y -= this->horizontal->super.size.y;
	}

	this->horizontal->super.position.x = 0;
	this->horizontal->super.position.y = this->super.size.y - this->horizontal->super.size.y;

	this->vertical->super.position.x = this->super.size.x - this->vertical->super.size.x;
	this->vertical->super.position.y = 0;

	if (this->horizontal->visible)
		this->viewport->super.size.y -= this->horizontal->super.size.y;

	if (this->vertical->visible)
		this->viewport->super.size.x -= this->vertical->super.size.x;

	t_ui_widget *widget = ui_widget_get_child(cast(this->viewport), 0);
	if (widget)
	{
		ui_scrollbar_set_max(this->vertical, widget->size.y - this->viewport->super.size.y);
		ui_scrollbar_set_max(this->horizontal, widget->size.x - this->viewport->super.size.x);
	}
	else
	{
		ui_scrollbar_set_max(this->vertical, 0);
		ui_scrollbar_set_max(this->horizontal, 0);
	}


	(void)data;
}

void
ui_scroll_draw(t_ui_scroll *scroll, void *data)
{
	ui_group_draw_widget(cast(scroll), true);
}

int
ui_scroll_event(t_ui_scroll *scroll, t_ui_event_base *event, void *data)
{
	if (event->type != UI_EVENT_TYPE_MOUSE_WHEEL_MOVED)
		return (UI_EVENT_CONTINUE);

	t_ui_event_mouse_wheel *wheel_event = cast(event);

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	bool shift = state[SDL_SCANCODE_LSHIFT];

	if (wheel_event->scroll.y)
	{
		if (shift)
		{
			int offset = scroll->horizontal->offset - wheel_event->scroll.y * 10;
			ui_scrollbar_set_offset(scroll->horizontal, offset);
		}
		else
		{
			int offset = scroll->vertical->offset - wheel_event->scroll.y * 10;
			ui_scrollbar_set_offset(scroll->vertical, offset);
		}
	}

	if (wheel_event->scroll.x)
	{
		int offset = scroll->horizontal->offset - wheel_event->scroll.x * 10;
		ui_scrollbar_set_offset(scroll->horizontal, offset);
	}

	printf("offset v%d\n", scroll->vertical->offset);

	scroll->viewport->offset = vector2i(scroll->horizontal->offset, scroll->vertical->offset);
	ui_widget_set_dirty(cast(scroll));

	return (UI_EVENT_CONSUME);
	(void)data;
}

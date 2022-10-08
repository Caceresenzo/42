/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrollbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scrollbar.h"

#define DEFAULT_SIZE (15)

static t_ui_widget_descriptor descriptor = {
	.name = "scrollbar",
	.size = sizeof(t_ui_scrollbar),
	.children_limit = 0,
	.handlers = {
		.describe = {
			.code = (void*)&ui_scrollbar_describe,
			.data = NULL
		},
		.draw = {
			.code = (void*)&ui_scrollbar_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_scrollbar_size,
			.data = NULL
		},
		.event = {
			.code = (void*)&ui_scrollbar_event,
			.data = NULL
		},
	}
};

t_ui_scrollbar*
ui_scrollbar_new(t_ui_scrollbar_orientation orientation)
{
	t_ui_scrollbar *this = cast(ui_widget_new(&descriptor));
	this->orientation = orientation;
	this->policy = UI_SCROLLBAR_POLICY_ALWAYS;
	this->visible = true;

	this->super.style.background_color = optional_int(0xff201c13);
	this->super.style.color = optional_int(0xff453a29);
	this->super.style.hover_color = optional_int(0xff575143);

	return (this);
}

void
ui_scrollbar_update_visibility(t_ui_scrollbar *this)
{
	if (this->policy == UI_SCROLLBAR_POLICY_ALWAYS)
		this->visible = true;
	else if (this->policy == UI_SCROLLBAR_POLICY_NEVER)
		this->visible = false;
	else if (this->policy == UI_SCROLLBAR_POLICY_AS_NEEDED)
		this->visible = this->max <= ui_scrollbar_get_component(this, this->super.size);

	ui_widget_set_dirty(cast(this));
}

void
ui_scrollbar_set_max(t_ui_scrollbar *this, int max)
{
	max = MAX(0, max);
	if (this->max == max)
		return;

	this->max = max;
	ui_scrollbar_update_visibility(this);
}

void
ui_scrollbar_set_offset(t_ui_scrollbar *this, int offset)
{
	int size = ui_scrollbar_get_component(this, this->super.size);
	offset = CLAMP(offset, 0, this->max - size);
	if (this->offset == offset)
		return;

	this->offset = offset;
	ui_scrollbar_update_visibility(this);
}

int
ui_scrollbar_get_component(t_ui_scrollbar *this, t_vector2i vector)
{
	if (this->orientation == UI_SCROLLBAR_ORIENTATION_VERTICAL)
		return (vector.y);
	return (vector.x);
}

void
ui_scrollbar_describe(t_ui_scrollbar *this, char *buffer, void *data)
{
	sprintf(buffer, "max=%d offset=%d visible=%d thumb.position=%d thumb.size=%d", this->max, this->offset, this->visible, this->thumb.position, this->thumb.size);
}

void
ui_scrollbar_size(t_ui_scrollbar *this, void *data)
{
	if (this->orientation == UI_SCROLLBAR_ORIENTATION_HORIZONTAL)
		this->super.size = vector2i(100, DEFAULT_SIZE * this->visible);
	else
		this->super.size = vector2i(DEFAULT_SIZE * this->visible, 100);

	ui_style_apply_size(cast(this));
	ui_scrollbar_update_visibility(this);

	(void)data;
}

void
ui_scrollbar_draw(t_ui_scrollbar *this, void *data)
{
	SDL_Rect rect = { 0, 0, this->super.size.x, this->super.size.y };
	SDL_FillRect(this->super._surface, &rect, this->super.style.background_color.value);

	if (this->visible)
	{
		int size = ui_scrollbar_get_component(this, this->super.size);
		if (size && this->max)
		{
			int ratio = this->max / size;
			if (ratio)
			{
				this->thumb.size = size / ratio;
				this->thumb.position = this->offset * (size - this->thumb.size) / (this->max - size);
			}
		}
		else
		{
			this->thumb.size = 0;
			this->thumb.position = 0;
		}
	}

	if (this->orientation == UI_SCROLLBAR_ORIENTATION_HORIZONTAL)
		rect = (SDL_Rect ) { this->thumb.position, 0, this->thumb.size, this->super.size.y };
	else
		rect = (SDL_Rect ) { 0, this->thumb.position, this->super.size.x, this->thumb.size };

	if (this->thumb.margin)
	{
		rect.x += this->thumb.margin;
		rect.y += this->thumb.margin;
		rect.w -= this->thumb.margin * 2;
		rect.h -= this->thumb.margin * 2;
	}

	int color = this->super.style.color.value;
	if (this->hovered)
		color = this->super.style.hover_color.value;

	SDL_FillRect(this->super._surface, &rect, color);
}

int
ui_scrollbar_event(t_ui_scrollbar *this, t_ui_event_base *event, void *data)
{
	t_ui_event_mouse *mouse = cast(event);

	if (event->type == UI_EVENT_TYPE_MOUSE_ENTERED)
	{
		this->hovered = true;
		return (UI_EVENT_CONTINUE);
	}

	if (event->type == UI_EVENT_TYPE_MOUSE_EXITED)
	{
		this->hovered = false;
		return (UI_EVENT_CONTINUE);
	}

	if (event->type == UI_EVENT_TYPE_MOUSE_DRAGGED || event->type == UI_EVENT_TYPE_MOUSE_PRESSED || event->type == UI_EVENT_TYPE_MOUSE_CLICKED)
	{
		int local = ui_scrollbar_get_component(this, mouse->local);
		int size = ui_scrollbar_get_component(this, this->super.size);

		int offset = local * this->max / size;
//		printf("local=%d offset=%d ", local, offset);
		offset -= (this->thumb.size / 2) * this->max / size;
//		printf("offset=%d\n", offset);

		ui_scrollbar_set_offset(this, offset);
		ui_scrollbar_on_scroll_call(this);

		return (UI_EVENT_CONSUME);
	}

	return (UI_EVENT_CONTINUE);
	(void)data;
}

void
ui_scrollbar_on_scroll_call(t_ui_scrollbar *this)
{
	ui_widget_function_int_call(cast(this), &this->on.scroll, this->offset);
}

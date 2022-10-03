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

static t_ui_widget_descriptor scrollbar_descriptor = {
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
	t_ui_scrollbar *scrollbar = cast(ui_widget_new(&scrollbar_descriptor));
	scrollbar->orientation = orientation;
	scrollbar->policy = UI_SCROLLBAR_POLICY_ALWAYS;
	scrollbar->visible = true;

	scrollbar->super.style.background_color = optional_int(0xff201c13);
	scrollbar->super.style.color = optional_int(0xff453a29);

	return (scrollbar);
}

void
ui_scrollbar_update_visibility(t_ui_scrollbar *scrollbar)
{
	if (scrollbar->policy == UI_SCROLLBAR_POLICY_ALWAYS)
		scrollbar->visible = true;
	else if (scrollbar->policy == UI_SCROLLBAR_POLICY_NEVER)
		scrollbar->visible = false;
	else if (scrollbar->policy == UI_SCROLLBAR_POLICY_AS_NEEDED)
	{
		if (scrollbar->orientation == UI_SCROLLBAR_ORIENTATION_HORIZONTAL)
			scrollbar->visible = scrollbar->max <= scrollbar->super.size.y;
		else
			scrollbar->visible = scrollbar->max <= scrollbar->super.size.x;
	}

	ui_widget_set_dirty(cast(scrollbar));
}

void
ui_scrollbar_set_max(t_ui_scrollbar *scrollbar, int max)
{
	max = MAX(0, max);
	if (scrollbar->max == max)
		return;

	scrollbar->max = max;
	ui_scrollbar_update_visibility(scrollbar);
}

void
ui_scrollbar_set_offset(t_ui_scrollbar *scrollbar, int offset)
{
	offset = CLAMP(offset, 0, scrollbar->max);
	if (scrollbar->offset == offset)
		return;

	scrollbar->offset = offset;
	ui_scrollbar_update_visibility(scrollbar);
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
		int size = this->super.size.y;
		if (this->orientation == UI_SCROLLBAR_ORIENTATION_HORIZONTAL)
			size = this->super.size.x;

		if (!size)
			size = 1;

		if (this->max)
		{
			this->thumb.size = size * 100 / this->max;
			printf("size=%d thumb.size=%d\n", size, this->thumb.size);
			this->thumb.position = this->offset * (size - this->thumb.size) / this->max;
		}
	}

	if (this->orientation == UI_SCROLLBAR_ORIENTATION_HORIZONTAL)
		rect = (SDL_Rect ) { this->thumb.position, 0, this->thumb.size, this->super.size.y };
	else
		rect = (SDL_Rect ) { 0, this->thumb.position, this->super.size.x, this->thumb.size };

	SDL_FillRect(this->super._surface, &rect, this->super.style.color.value);
}

int
ui_scrollbar_event(t_ui_scrollbar *scrollbar, t_ui_event_base *event, void *data)
{
	return (UI_EVENT_CONTINUE);
	(void)data;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:44:59 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:44:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkbox.h"

static t_ui_widget_descriptor descriptor = {
	.name = "checkbox",
	.size = sizeof(t_ui_checkbox),
	.children_limit = 0,
	.handlers = {
		.describe = {
			.code = (void*)&ui_checkbox_describe,
			.data = NULL
		},
		.draw = {
			.code = (void*)&ui_checkbox_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_checkbox_size,
			.data = NULL
		},
		.event = {
			.code = (void*)&ui_checkbox_event,
			.data = NULL
		},
	}
};

t_ui_checkbox*
ui_checkbox_new(const char *text)
{
	t_ui_checkbox *checkbox = cast(ui_widget_new(&descriptor));
	checkbox->text = strdup(text);

	return (checkbox);
}

void
ui_checkbox_set_text(t_ui_checkbox *this, const char *text)
{
	free(this->text);

	if (text)
		this->text = strdup(text);
	else
		this->text = NULL;

	ui_widget_set_dirty(cast(this));
}

void
ui_checkbox_set_checked(t_ui_checkbox *this, bool value)
{
	if (this->checked != value)
	{
		this->checked = value;
		ui_widget_set_dirty(cast(this));
	}
}

void
ui_checkbox_toggle(t_ui_checkbox *this)
{
	this->checked = !this->checked;
	ui_widget_set_dirty(cast(this));
}

void
ui_checkbox_size(t_ui_checkbox *this, void *data)
{
	assert(this->super.window);
	this->super.size = ui_font_size(this->super.window->app->font, this->text);
	this->super.size.x += this->super.window->app->font->size;
	ui_style_apply_size(cast(this));
	(void)data;
}

void
ui_checkbox_draw(t_ui_checkbox *this, void *data)
{
	int color = optional_int_or_else(this->super.style.color, 0xffffffff);
	int size = this->super.window->app->font->size;

	SDL_Rect box = { size / 4, size / 4, size / 2, size / 2 };
	SDL_FillRect(this->super._surface, &box, color);

	box.x += 1;
	box.y += 1;
	box.w -= 2;
	box.h -= 2;
	SDL_FillRect(this->super._surface, &box, 0);

	if (this->checked)
	{
		box.x += 2;
		box.y += 2;
		box.w -= 4;
		box.h -= 4;
		SDL_FillRect(this->super._surface, &box, color);
	}

	ui_font_draw(
		this->super.window->app->font,
		this->super._surface,
		this->text,
		vector2i(size, 0),
		color);

	(void)data;
}

void
ui_checkbox_describe(t_ui_checkbox *this, char *buffer, void *data)
{
	sprintf(buffer, "text=%s checked=%d", this->text, this->checked);
}

int
ui_checkbox_event(t_ui_scrollbar *this, t_ui_event_base *event, void *data)
{
	t_ui_event_mouse *mouse_event = cast(event);

	if (event->type == UI_EVENT_TYPE_MOUSE_CLICKED)

		ui_checkbox_toggle(this);
	else
		return (UI_EVENT_CONTINUE);
	return (UI_EVENT_CONSUME);
}

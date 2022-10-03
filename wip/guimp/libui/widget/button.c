/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:44:59 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:44:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

static t_ui_widget_descriptor button_descriptor = {
	.name = "button",
	.size = sizeof(t_ui_button),
	.children_limit = 1,
	.handlers = {
		.draw = {
			.code = (void*)&ui_button_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_button_size,
			.data = NULL
		},
		.event = {
			.code = (void*)&ui_button_event,
			.data = NULL
		}
	}
};

t_ui_button*
ui_button_new(void)
{
	t_ui_button *button = cast(ui_widget_new(&button_descriptor));
	button->super.traversable = false;
	button->color = 0xFF888888;
	button->hover_color = 0xFF000000;
	button->pressed_color = 0xFF555555;

	return (button);
}

bool
ui_button_set_state(t_ui_button *button, t_ui_button_state state)
{
	if (button->state == state)
		return (false);
	button->state = state;
	ui_widget_set_dirty(cast(button));
	return (true);
}

void
ui_button_size(t_ui_button *button, void *data)
{
	ui_group_size_widget(cast(button), UI_GROUP_DIRECTION_HORIZONTAL);

	ui_style_apply_size(cast(button));
}

void
ui_button_draw(t_ui_button *button, void *data)
{
	int color;

	color = button->color;
	if (button->state == UI_BUTTON_STATE_HOVER)
		color = button->hover_color;
	else if (button->state == UI_BUTTON_STATE_PRESSED)
		color = button->pressed_color;

	SDL_FillRect(button->super._surface, NULL, color);

	ui_group_draw_widget(cast(button), true);
	(void)data;
}

void
ui_button_event(t_ui_button *button, t_ui_event_base *event, void *data)
{
	t_ui_event_mouse *mouse_event = cast(event);

	if (event->type == UI_EVENT_TYPE_MOUSE_PRESSED && mouse_event->button == 1)
		ui_button_set_state(button, UI_BUTTON_STATE_PRESSED);
	else if (event->type == UI_EVENT_TYPE_MOUSE_ENTERED || (event->type == UI_EVENT_TYPE_MOUSE_RELEASED && mouse_event->button == 1))
		ui_button_set_state(button, UI_BUTTON_STATE_HOVER);
	else if (event->type == UI_EVENT_TYPE_MOUSE_EXITED)
		ui_button_set_state(button, UI_BUTTON_STATE_NONE);

	if (event->type == UI_EVENT_TYPE_MOUSE_CLICKED)
		ui_widget_function_call(cast(button), &button->on.click);

	(void)data;
}

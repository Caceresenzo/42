/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:44:59 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:44:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "label.h"

static t_ui_widget_descriptor label_descriptor = {
	.name = "label",
	.size = sizeof(t_ui_label),
	.children_limit = 0,
	.handlers = {
		.describe = {
			.code = (void*)&ui_label_describe,
			.data = NULL
		},
		.draw = {
			.code = (void*)&ui_label_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_label_size,
			.data = NULL
		},
	}
};

t_ui_label*
ui_label_new(const char *text)
{
	t_ui_label *label = cast(ui_widget_new(&label_descriptor));
	label->text = strdup(text);

	return (label);
}

void
ui_label_set_text(t_ui_label *label, const char *text)
{
	free(label->text);

	if (text)
		label->text = strdup(text);
	else
		label->text = NULL;

	ui_widget_set_dirty(cast(label));
}

void
ui_label_size(t_ui_label *this, void *data)
{
	assert(this->super.window);
	this->super.size = ui_font_size(this->super.window->app->font, this->text);
	ui_style_apply_size(cast(this));
	(void)data;
}

void
ui_label_draw(t_ui_label *label, void *data)
{
	ui_font_draw(
		label->super.window->app->font,
		label->super._surface,
		label->text,
		vector2i_zero(),
		optional_int_or_else(label->super.style.color, 0xffffffff));

	(void)data;
}

void
ui_label_describe(t_ui_label *label, char *buffer, void *data)
{
	sprintf(buffer, "text=%s", label->text);
}

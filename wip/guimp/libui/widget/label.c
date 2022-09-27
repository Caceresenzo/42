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
	.size = sizeof(t_ui_label)
};

t_ui_label*
ui_label_new(const char *text)
{
	t_ui_label *label = cast(ui_widget_new(&label_descriptor));
	label->super.on.size.function = cast(&ui_label_size);
	label->super.on.draw.function = cast(&ui_label_draw);
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
ui_label_set_background_color(t_ui_label *label, t_color background_color)
{
	label->background_color = background_color;
	ui_widget_set_dirty(cast(label));
}

void
ui_label_size(t_ui_label *label, void *data)
{
	size_t len = 0;
	size_t line = 1;

	char *str = label->text;
	while (*str)
	{
		++len;
		if (*str == '\n')
			++line;
		++str;
	}

	label->super.size = (t_vector2i ) { .x = len * 8, .y = line * 16 };
	(void)data;
}

void
ui_label_draw(t_ui_label *label, void *data)
{
	SDL_LockSurface(label->super._surface);
	SDL_FillRect(label->super._surface, NULL, SDL_MapRGB(label->super._surface->format, label->background_color.red, label->background_color.green, label->background_color.blue));
	SDL_UnlockSurface(label->super._surface);

	(void)data;
}

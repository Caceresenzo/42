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
	.handlers = {
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
ui_label_set_background_color(t_ui_label *label, t_color background_color)
{
	label->background_color = background_color;
	ui_widget_set_dirty(cast(label));
}

void
ui_label_size(t_ui_label *label, void *data)
{
	t_vector2i size = { 0, 0 };

	char *str = label->text;
	char *line_start = label->text;
	while (*str)
	{
		if (*str == '\n')
		{
			*str = '\0';
			int w, h;
			TTF_SizeText(label->super.window->app->font, line_start, &w, &h);
			size.x = MAX(size.x, w);
			size.y += h;
			*str = '\n';
			line_start = str + 1;
		}
		++str;
	}

	int w, h;
	TTF_SizeText(label->super.window->app->font, line_start, &w, &h);
	size.x = MAX(size.x, w);
	size.y += h;

	label->super.size = size;
	ui_style_apply_size(cast(label));
	(void)data;
}

void
ui_label_draw(t_ui_label *label, void *data)
{
	SDL_Color color = { 255, 255, 255 };
	if (label->super.style.text_color.present)
		*((int*) &color) = label->super.style.text_color.value;

	//	SDL_LockSurface(label->super._surface);
//	SDL_FillRect(label->super._surface, NULL, SDL_MapRGBA(label->super._surface->format, 0, 0, 0, 0));
//	SDL_FillRect(label->super._surface, NULL, SDL_MapRGBA(label->super._surface->format, label->background_color.red, label->background_color.green, label->background_color.blue, 0));

	int y = 0;

	char *str = label->text;
	char *line_start = label->text;
	while (*str)
	{
		if (*str == '\n')
		{
			*str = '\0';

			SDL_Surface *line = TTF_RenderText_Solid(label->super.window->app->font, line_start, color);
			SDL_Rect destrec = { 0, y, line->w, line->h };
			SDL_BlitSurface(line, NULL, label->super._surface, &destrec);
			SDL_FreeSurface(line);

			y += line->h;

			*str = '\n';
			line_start = str + 1;
		}
		++str;
	}

	SDL_Surface *line = TTF_RenderText_Solid(label->super.window->app->font, line_start, color);
	SDL_Rect destrec = { 0, y, line->w, line->h };
	SDL_BlitSurface(line, NULL, label->super._surface, &destrec);
	SDL_FreeSurface(line);

//	setPixel(label->super._surface, 0, 0, 0, 127, 1, 1);

//	SDL_BlitSurface(line, NULL, label->super._surface, NULL);

//	SDL_UnlockSurface(label->super._surface);

	(void)data;
}

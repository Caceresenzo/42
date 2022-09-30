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

static int
ui_label_event(t_ui_label *label, t_ui_event_base *event, void *data)
{
	if (event->type == UI_EVENT_TYPE_MOUSE_MOTION)
		ui_label_set_background_color(label, (t_color ) { rand() % 255, rand() % 255, rand() % 255 });
	else if (event->type == UI_EVENT_TYPE_MOUSE_PRESSED)
		ui_label_set_background_color(label, (t_color ) { 0, 0, 0 });
	else if (event->type == UI_EVENT_TYPE_MOUSE_RELEASED)
		ui_label_set_background_color(label, (t_color ) { 255, 255, 255 });
	return (UI_EVENT_CONSUME);
	(void)data;
}

t_ui_label*
ui_label_new(const char *text)
{
	t_ui_label *label = cast(ui_widget_new(&label_descriptor));
	label->super.handlers.size.function = cast(&ui_label_size);
	label->super.handlers.draw.function = cast(&ui_label_draw);
	label->super.handlers.event.function = cast(&ui_label_event);
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
	(void)data;
}

void
ui_label_draw(t_ui_label *label, void *data)
{
	SDL_Color White = { 255, 255, 255 };

	//	SDL_LockSurface(label->super._surface);
	SDL_FillRect(label->super._surface, NULL, SDL_MapRGB(label->super._surface->format, label->background_color.red, label->background_color.green, label->background_color.blue));

	int y = 0;

	char *str = label->text;
	char *line_start = label->text;
	while (*str)
	{
		if (*str == '\n')
		{
			*str = '\0';

			SDL_Surface *line = TTF_RenderText_Solid(label->super.window->app->font, line_start, White);
			SDL_Rect destrec = { 0, y, line->w, line->h };
			SDL_BlitSurface(line, NULL, label->super._surface, &destrec);
			SDL_FreeSurface(line);

			y += line->h;

			*str = '\n';
			line_start = str + 1;
		}
		++str;
	}

	SDL_Surface *line = TTF_RenderText_Solid(label->super.window->app->font, line_start, White);
	SDL_Rect destrec = { 0, y, line->w, line->h };
	SDL_BlitSurface(line, NULL, label->super._surface, &destrec);
	SDL_FreeSurface(line);

//	SDL_BlitSurface(line, NULL, label->super._surface, NULL);

//	SDL_UnlockSurface(label->super._surface);

	(void)data;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:38:20 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 21:38:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

bool
ui_font_load(t_ui_application *app, const char *path, int size)
{
	app->font = calloc(sizeof(t_font), 1);
	app->font->name = path;
	app->font->size = size;
	app->font->_font = TTF_OpenFont(path, size);
	if (!app->font->_font)
		sdl_abort("TTF_OpenFont");
	return (true);
}

t_vector2i
ui_font_size(t_font *font, char *text)
{
	int width;
	int height;
	t_vector2i size = { 0, 0 };

	char *str = text;
	char *line_start = text;
	while (*str)
	{
		if (*str == '\n')
		{
			// TODO Do not modify the string
			*str = '\0';
			TTF_SizeText(font->_font, line_start, &width, &height);
			size.x = MAX(size.x, width);
			size.y += height;
			*str = '\n';
			line_start = str + 1;
		}
		++str;
	}

	TTF_SizeText(font->_font, line_start, &width, &height);
	size.x = MAX(size.x, width);
	size.y += height;

	return (size);
}

void
ui_font_draw(t_font *font, SDL_Surface *surface, char *text, t_vector2i position, int color)
{
	char *str = text;
	char *line_start = text;

	while (*str)
	{
		if (*str == '\n')
		{
			*str = '\0';

			SDL_Surface *line = TTF_RenderText_Solid(font->_font, line_start, sdl_as_color(color));
			if (!line)
				sdl_abort("TTF_RenderText_Solid");

			SDL_Rect destrec = { position.x, position.y, line->w, line->h };
			SDL_BlitSurface(line, NULL, surface, &destrec);
			SDL_FreeSurface(line);

			position.y += line->h;

			*str = '\n';
			line_start = str + 1;
		}
		++str;
	}

	SDL_Surface *line = TTF_RenderText_Solid(font->_font, line_start, sdl_as_color(color));
	if (!line)
		sdl_abort("TTF_RenderText_Solid");

	SDL_Rect destrec = { position.x, position.y, line->w, line->h };
	SDL_BlitSurface(line, NULL, surface, &destrec);
	SDL_FreeSurface(line);
}

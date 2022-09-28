/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:39:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 23:39:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static t_ui_widget_descriptor image_descriptor = {
	.name = "image",
	.size = sizeof(t_ui_image)
};

t_ui_image*
ui_image_new(const char *path)
{
	t_ui_image *image;
	t_error error;

	image = cast(ui_widget_new(&image_descriptor));
	if (!image)
		return (NULL);
	image->super.size_handler.function = cast(&ui_image_size);
	image->super.draw_handler.function = cast(&ui_image_draw);
	error = ui_image_set_picture(image, path);
	if (error.present)
		printf("warning: could not load `%s`: %s\n", path, error.message);
	return (image);
}

t_error
ui_image_set_picture(t_ui_image *image, const char *path)
{
	SDL_Surface *picture;
	t_error error;

	picture = IMG_Load(path);
	if (!picture)
	{
		error = (t_error ) { .present = true, .message = IMG_GetError() };
		return (error);
	}
	image->picture = picture;
	ui_widget_set_dirty(cast(image));
	error = (t_error ) { .present = false, .message = NULL };
	return (error);
}

void
ui_image_size(t_ui_image *image, void *data)
{
	if (image->picture)
	{
		image->super.size.x = image->picture->w;
		image->super.size.y = image->picture->h;
	}
	else
		image->super.size = vector2i_zero();
	(void)data;
}

void
ui_image_draw(t_ui_image *image, void *data)
{
	if (image->picture)
		SDL_BlitSurface(image->picture, NULL, image->super._surface, NULL);

	(void)data;
}

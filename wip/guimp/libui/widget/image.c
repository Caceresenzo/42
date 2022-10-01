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
	.size = sizeof(t_ui_image),
	.handlers = {
		.draw = {
			.code = (void*)&ui_image_draw,
			.data = NULL
		},
		.size = {
			.code = (void*)&ui_image_size,
			.data = NULL
		}
	}
};

t_ui_image*
ui_image_new(const char *path)
{
	t_ui_image *image;
	t_ui_error error;

	image = cast(ui_widget_new(&image_descriptor));
	image->super.traversable = false;
	image->super.focusable = false;

	error = ui_image_set_picture(image, path);
	if (error.present)
		printf("warning: could not load `%s`: %s\n", path, error.message);

	return (image);
}

t_ui_error
ui_image_set_picture(t_ui_image *image, const char *path)
{
	SDL_Surface *picture;

	picture = IMG_Load(path);
	if (!picture)
		return (ui_error_present(IMG_GetError()));
	if (image->picture)
		SDL_FreeSurface(image->picture);
	image->picture = picture;
	ui_widget_set_dirty(cast(image));
	return (ui_error_absent());
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

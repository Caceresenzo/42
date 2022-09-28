/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:38:41 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 23:38:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_IMAGE_H
# define WIDGET_IMAGE_H

# include "../ui.h"

typedef struct s_ui_image
{
	t_ui_widget super;
	SDL_Surface *picture;
} t_ui_image;

t_ui_image*
ui_image_new(const char *path);

t_error
ui_image_set_picture(t_ui_image *image, const char *path);

void
ui_image_size(t_ui_image *image, void *data);

void
ui_image_draw(t_ui_image *image, void *data);

#endif

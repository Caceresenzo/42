/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:38:41 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 23:38:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_CANVAS_H
# define WIDGET_CANVAS_H

# include "../ui.h"

typedef struct s_ui_canvas
{
	t_ui_widget super;
	SDL_Surface *surface;
	t_vector2i dimension;
	int color;
} t_ui_canvas;

t_ui_canvas*
ui_canvas_new(t_vector2i size);

void
ui_canvas_set_pixel(t_ui_canvas *canvas, t_vector2i position, int color);

void
ui_canvas_size(t_ui_canvas *canvas, void *data);

void
ui_canvas_draw(t_ui_canvas *canvas, void *data);

void
ui_canvas_event(t_ui_canvas *canvas, t_ui_event_base *event, void *data);

#endif

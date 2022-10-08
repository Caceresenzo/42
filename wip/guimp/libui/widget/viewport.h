/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_VIEWPORT_H
# define WIDGET_VIEWPORT_H

# include "../ui.h"

typedef struct s_ui_viewport
{
	t_ui_widget super;
	t_vector2i offset;
} t_ui_viewport;

t_ui_viewport*
ui_viewport_new(void);

bool
ui_viewport_set_offset(t_ui_viewport *this, t_vector2i offset);

void
ui_viewport_describe(t_ui_viewport *this, char *buffer, void *data);

void
ui_viewport_size(t_ui_viewport *viewport, void *data);

void
ui_viewport_draw(t_ui_viewport *viewport, void *data);

void
ui_viewport_hitscan_interceptor(t_ui_viewport *viewport, t_vector2i *point, void *data);

#endif

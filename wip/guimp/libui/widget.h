/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:30:53 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:30:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_H
# define WIDGET_H

# include "ui.h"

t_ui_widget*
ui_widget_new(t_ui_widget_descriptor *descriptor);

void
ui_widget_size(t_ui_widget *widget);

void
ui_widget_draw(t_ui_widget *widget);

void
ui_widget_set_dirty(t_ui_widget *widget);

bool
ui_widget_is_inside(t_ui_widget *widget, t_vector2i point);

void
ui_widget_draw_call(t_ui_widget *widget);

void
ui_widget_size_call(t_ui_widget *widget);

int
ui_widget_event_call(t_ui_widget *widget, const t_ui_event_base *event);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:27:12 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:27:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "core.h"

t_ui_window*
ui_window_new(t_ui_application *app, t_vector2i position, t_vector2i size, uint32_t flags);

void
ui_window_destroy(t_ui_window *window);

const char*
ui_window_get_title(t_ui_window *window);

void
ui_window_set_title(t_ui_window *window, const char *title);

t_ui_widget*
ui_window_set_root(t_ui_window *window, t_ui_widget *widget);

void
ui_widget_add(t_ui_widget *parent, t_ui_widget *widget);

void
ui_window_draw(t_ui_window *window);

void
ui_window_dispatch(const t_ui_event_base *event);

#endif

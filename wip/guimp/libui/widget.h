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

#endif

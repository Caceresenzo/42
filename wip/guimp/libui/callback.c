/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:25:53 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:25:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void
ui_callback_size_call(t_ui_widget *widget)
{
	if (widget->size_handler.function)
		widget->size_handler.function(widget, widget->size_handler.data);
}

void
ui_callback_draw_call(t_ui_widget *widget)
{
	if (widget->draw_handler.function)
		widget->draw_handler.function(widget, widget->draw_handler.data);
}

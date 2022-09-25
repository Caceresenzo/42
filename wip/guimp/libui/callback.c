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
	if (widget->on.size.function)
		widget->on.size.function(widget, widget->on.size.data);
}

void
ui_callback_draw_call(t_ui_widget *widget)
{
	if (widget->on.draw.function)
		widget->on.draw.function(widget, widget->on.draw.data);
}

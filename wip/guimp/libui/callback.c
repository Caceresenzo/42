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
	if (widget->handlers.size.function)
		widget->handlers.size.function(widget, widget->handlers.size.data);
}

void
ui_callback_draw_call(t_ui_widget *widget)
{
	if (widget->handlers.draw.function)
		widget->handlers.draw.function(widget, widget->handlers.draw.data);
}

int
ui_callback_event_call(t_ui_widget *widget, const t_ui_event_base *event)
{
	if (widget->handlers.event.function)
		return (widget->handlers.event.function(widget, event, widget->handlers.event.data));
	return (UI_EVENT_CONTINUE);
}

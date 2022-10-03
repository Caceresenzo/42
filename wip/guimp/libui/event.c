/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:39:45 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/03 17:39:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

bool
ui_event_type_is_mouse(t_ui_event_type type)
{
	return (type == UI_EVENT_TYPE_MOUSE_MOVED
		|| type == UI_EVENT_TYPE_MOUSE_DRAGGED
		|| type == UI_EVENT_TYPE_MOUSE_CLICKED
		|| type == UI_EVENT_TYPE_MOUSE_ENTERED
		|| type == UI_EVENT_TYPE_MOUSE_EXITED
		|| type == UI_EVENT_TYPE_MOUSE_PRESSED
		|| type == UI_EVENT_TYPE_MOUSE_RELEASED);
}

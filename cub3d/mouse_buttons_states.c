/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_buttons_states.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:07:50 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 12:07:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mouse.h"

int		g_mouse_buttons_states[MOUSE_BUTTON_COUNT];
int		g_mouse_button_last = -1;

void
	mouse_button_state_initialize(void)
{
	size_t	index;

	index = 0;
	while (index < MOUSE_BUTTON_COUNT)
	{
		g_mouse_buttons_states[index] = 0;
		index++;
	}
}

int
	mouse_button_state_set(int button, int state)
{
	int		was;

	was = g_mouse_buttons_states[button];
	g_mouse_buttons_states[button] = state;
	if (state == STATE_PRESSED)
		g_mouse_button_last = button;
	return (was);
}

int
	mouse_button_state_get(int button)
{
	return (g_mouse_buttons_states[button]);
}

int
	mouse_button_last_get(void)
{
	return (g_mouse_button_last);
}

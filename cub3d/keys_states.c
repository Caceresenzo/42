/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:07:50 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 12:07:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "cub3d.h"

int		g_keys_states[KEY_COUNT];

void
	key_state_initialize(void)
{
	size_t	index;

	index = 0;
	while (index < KEY_COUNT)
	{
		g_keys_states[index] = 0;
		index++;
	}
}

int
	key_state_set(int keycode, int state)
{
	int		was;

	was = g_keys_states[keycode];
	g_keys_states[keycode] = state;
	return (was);
}

int
	key_state_get(int keycode)
{
	return (g_keys_states[keycode]);
}

int
	key_state_get2(int keycode1, int keycode2)
{
	return (key_state_get(keycode1) || key_state_get(keycode2));
}

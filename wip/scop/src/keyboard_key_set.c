/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_key_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:29:55 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 14:29:55 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void
keyboard_key_set(int keycode, bool state)
{
	if (!keyboard_is_in_range(state))
		return;

	keyboard_key_states()[keycode] = state;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_key_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:31:56 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 14:31:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

bool
keyboard_key_get(int keycode)
{
	if (!keyboard_is_in_range(keycode))
		return (KEY_STATE_RELEASED);

	return (keyboard_key_states()[keycode]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_key_states.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:29:07 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 14:29:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

bool*
keyboard_key_states(void)
{
	static bool states[KEY_COUNT] = { 0 };

	return (states);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_is_in_range.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:32:53 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 14:32:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

bool
keyboard_is_in_range(int keycode)
{
	return (keycode >= 0 && keycode < KEY_COUNT);
}

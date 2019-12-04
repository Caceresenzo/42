/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_mouse_pressed.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:23:22 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 17:23:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_mouse_pressed(int button, int x, int y, t_engine *engine)
{
	ft_fake_use(&engine);
	mouse_button_state_set(button, STATE_PRESSED);
	mouse_pos_last_click_update(x, y);
	return (0);
}

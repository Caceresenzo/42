/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_key_pressed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:50:25 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 16:50:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_key_pressed(int keycode, t_engine *engine)
{
	ft_fake_use(&engine);
	key_state_set(keycode, STATE_PRESSED);
	if (keycode == KEY_ESCAPE)
		engine_handle_exit(engine, 1);
	return (0);
}

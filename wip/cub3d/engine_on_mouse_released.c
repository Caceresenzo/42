/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_mouse_released.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:23:38 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 17:23:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_mouse_released(int button, int x, int y, t_engine *engine)
{
	FAKE_USE(engine);
	printf("EVENT: on_mouse_released: button = %d, x = %d, y = %d\n", button, x, y);
	mouse_button_state_set(button, STATE_RELEASED);
	return (0);
}

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
	ft_fake_use(&engine);
	ft_fake_use(&x);
	ft_fake_use(&y);
	mouse_button_state_set(button, STATE_RELEASED);
	return (0);
}

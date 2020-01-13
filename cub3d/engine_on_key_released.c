/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_key_released.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:59:40 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 16:59:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_key_released(int keycode, t_engine *engine)
{
	ft_fake_use(&engine);
	key_state_set(keycode, STATE_RELEASED);
	return (0);
}

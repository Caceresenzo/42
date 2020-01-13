/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_mouse_move.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:23:50 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 17:23:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_mouse_move(int x, int y, t_engine *engine)
{
	ft_fake_use(&engine);
	mouse_pos_current_update(x, y);
	return (0);
}

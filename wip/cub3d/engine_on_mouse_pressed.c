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
	FAKE_USE(engine);
	printf("EVENT: on_mouse_pressed: button = %d, x = %d, y = %d\n", button, x, y);
	return (0);
}

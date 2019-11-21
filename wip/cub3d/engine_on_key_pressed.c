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
	char *str;

	printf("EVENT: on_key_pressed: keycode = %d\n", keycode);
	key_state_set(keycode, STATE_PRESSED);
	if (keycode == KEY_SPACE)
		str = ft_strdup(" ");
	else if (keycode == KEY_DELETE)
		str = (char *)-1;
	else
		str = key_get_str(keycode);
	if (str != NULL)
	{
		if (str == (char *)-1)
		{
			str = engine->str;
			engine->str = ft_calloc(ft_strlen(str), sizeof(char));
			ft_memcpy(engine->str, str, ft_strlen(str) - 1);
		}
		else
			engine->str = ft_strjoin(engine->str, str);
	}
	printf("%s\n", key_get_str(keycode));
	return (0);
}

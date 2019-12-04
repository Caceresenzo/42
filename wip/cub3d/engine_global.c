/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 11:34:02 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 11:34:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_engine	*g_engine = NULL;

t_engine
	*engine_global_set(t_engine *engine)
{
	g_engine = engine;
	return (engine);
}

t_engine
	*engine_global_get(void)
{
	return (g_engine);
}

int
	engine_global_is_set(void)
{
	return (g_engine != NULL);
}

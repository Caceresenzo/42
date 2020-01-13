/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_handle_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:18:12 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 18:18:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	i_engine_error_clear_memory(void)
{
	if (engine_global_is_set())
		engine_handle_exit(engine_global_get(), 0);
}

void
	*engine_error(char *error)
{
	ft_putendl_fd("Error", ERR);
	ft_putstr_fd(error, ERR);
	free(error);
	ft_putchar_fd('\n', ERR);
	i_engine_error_clear_memory();
	exit(1);
	return (NULL);
}

void
	*engine_error_raison(char *error)
{
	ft_putendl_fd("Error", ERR);
	ft_putstr_fd(error, ERR);
	free(error);
	if (errno != 0)
	{
		ft_putstr_fd(", reason: ", ERR);
		ft_putendl_fd(strerror(errno), ERR);
	}
	else
		ft_putchar_fd('\n', ERR);
	i_engine_error_clear_memory();
	exit(1);
	return (NULL);
}

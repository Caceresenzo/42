/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:23:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:23:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	err_print_usage(void)
{
	size_t	index;

	x_putstr_fd("usage: "PROGRAM": ", ERR);
	index = 0;
	while (index < NBR_OF_PARAMETER - 1)
	{
		x_putstr_fd(g_parameters[index], ERR);
		x_putstr_fd(" ", ERR);
		index++;
	}
	x_putstr_fd("[", ERR);
	x_putstr_fd(g_parameters[index], ERR);
	x_putstr_fd("]\n", ERR);
	return (1);
}

int
	err_param_not_int(int param)
{
	x_putstr_fd(PROGRAM": ", ERR);
	x_putstr_fd(g_parameters[param], ERR);
	x_putstr_fd(": must be a valid (and positive) integer\n", ERR);
	return (1);
}

int
	err_must_be_at_least_1_philo(void)
{
	x_putstr_fd(PROGRAM": must be at least 1 philosopher\n", ERR);
	return (1);
}

int
	err_pthread(int err, int for_mutex)
{
	if (for_mutex)
		x_putstr_fd(PROGRAM": failed to create mutex, reason: ", ERR);
	else
		x_putstr_fd(PROGRAM": failed to create thread, reason: ", ERR);
	x_putstr_fd(strerror(err), ERR);
	x_putstr_fd(" (", ERR);
	x_putnbr_fd(err, ERR);
	x_putstr_fd(")\n", ERR);
	return (err);
}

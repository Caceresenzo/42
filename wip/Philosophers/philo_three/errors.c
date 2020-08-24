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

char	**g_parameters = (char *[]){
	"number_of_philosopher",
	"time_to_die",
	"time_to_eat",
	"time_to_sleep",
	"number_of_time_each_philosophers_must_eat"
};

int
	err_print_usage(void)
{
	size_t	index;

	ft_putstr_fd("usage: "PROGRAM": ", FD_ERR);
	index = 0;
	while (index < NBR_OF_PARAMETER - 1)
	{
		ft_putstr_fd("<", FD_ERR);
		ft_putstr_fd(g_parameters[index], FD_ERR);
		ft_putstr_fd("> ", FD_ERR);
		index++;
	}
	ft_putstr_fd("[", FD_ERR);
	ft_putstr_fd(g_parameters[index], FD_ERR);
	ft_putstr_fd("]\n", FD_ERR);
	return (1);
}

int
	err_param_not_int(int param)
{
	ft_putstr_fd(PROGRAM": ", FD_ERR);
	ft_putstr_fd(g_parameters[param], FD_ERR);
	ft_putstr_fd(": must be a valid (and positive) integer\n", FD_ERR);
	return (1);
}

int
	err_must_be_at_least_1_philo(void)
{
	ft_putstr_fd(PROGRAM": must be at least 1 philosopher\n", FD_ERR);
	return (1);
}

int
	err_errno(int err, int child_id)
{
	char	msg[1024];
	size_t	len;

	if (err)
	{
		len = ft_sputstr(msg, PROGRAM": error: ");
		if (child_id)
		{
			len += ft_sputstr(msg + len, "child #");
			len += ft_sputnbr(msg + len, child_id);
			len += ft_sputstr(msg + len, ": ");
		}
		len += ft_sputstr(msg + len, strerror(err));
		len += ft_sputstr(msg + len, "\n");
		write(FD_ERR, msg, len);
	}
	return (err);
}

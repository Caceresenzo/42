/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:53:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:53:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#if 0

void __attribute__((destructor))
	on_stop(void)
{
	while (1)
		;
}

#endif

static bool
	atoi_strict(int *dst, char *str)
{
	bool	err;

	err = false;
	*dst = ft_atoi(str, &err);
	return (err);
}

int
	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (err_print_usage());
	if (atoi_strict(&(g_params.nbr_of_philo), argv[1]))
		return (err_param_not_int(0));
	else if (g_params.nbr_of_philo < 1)
		return (err_must_be_at_least_1_philo());
	if (atoi_strict(&(g_params.time_to_die), argv[2]))
		return (err_param_not_int(1));
	if (atoi_strict(&(g_params.time_to_eat), argv[3]))
		return (err_param_not_int(2));
	if (atoi_strict(&(g_params.time_to_sleep), argv[4]))
		return (err_param_not_int(3));
	g_params.nbr_must_eat = -1;
	if (argc == 6)
		if (atoi_strict(&(g_params.nbr_must_eat), argv[5]))
			return (err_param_not_int(4));
	if (g_params.nbr_must_eat == 0)
		return (0);
	return (err_errno(ph_main(), false));
}

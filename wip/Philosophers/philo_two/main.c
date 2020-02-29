/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:19:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:19:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** __attribute__((destructor))
** void
** 	destructor(void)
** {
** 	while (1);
** }
*/

int
	main(int argc, char **argv)
{
	t_param	param;
	int		err;

	if (argc < 5 || argc > 6)
		return (err_print_usage());
	param.nbr_of_philo = x_atoi(argv[1], &err);
	if (err)
		return (err_param_not_int(0));
	if (param.nbr_of_philo < 1)
		return (err_must_be_at_least_1_philo());
	param.time_to_die = x_atoi(argv[2], &err);
	if (err)
		return (err_param_not_int(1));
	param.time_to_eat = x_atoi(argv[3], &err);
	if (err)
		return (err_param_not_int(2));
	param.time_to_sleep = x_atoi(argv[4], &err);
	if (err)
		return (err_param_not_int(3));
	param.nbr_must_eat = -1;
	if (argc == 6)
		param.nbr_must_eat = x_atoi(argv[5], &err);
	if (argc == 6 && err)
		return (err_param_not_int(4));
	return (philosophers_run(param));
}

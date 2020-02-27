/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:20:43 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:20:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	**g_parameters = (char *[]){
	(char *)"number_of_philosopher",
	(char *)"time_to_die",
	(char *)"time_to_eat",
	(char *)"time_to_sleep",
	(char *)"number_of_time_each_philosophers_must_eat"
};

char	**g_man_states = (char *[]){
	(char *)"NONE",
	(char *)"is sleeping",
	(char *)"is thinking",
	(char *)"is eating",
	(char *)"time_to_sleep",
	(char *)"died"
};

int
	philosophers_run(t_param param)
{
	t_man	*root;
	int		err;

	root = philosophers_ring_create(param);
	if ((err = philosophers_ring_forks(param, root)) != 0)
		return (err_pthread(err, 1));
	philosophers_debug_print_ring(root);
	if ((err = philosophers_ring_threader(root)) != 0)
		return (err_pthread(err, 0));
	while (1)
		;
	return (0);
}

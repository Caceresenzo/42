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
	(char *)"has taken a fork",
	(char *)"is eating",
	(char *)"died"
};

int
	philosophers_run(t_param param)
{
	t_man	*root;
	sem_t	*forks;
	int		err;

	root = philosophers_ring_create(param);
	forks = forks_create(PROGRAM_SEM_MAIN, &err, param.nbr_of_philo);
	if (forks == NULL || err)
		return (err_pthread(err, 1));
	philosophers_ring_forks(root, forks);
	philosophers_ring_attach_param(root, &param);
	philosophers_status_sem_init();
	if ((err = philosophers_ring_threader(root)) != 0)
		return (err_pthread(err, 0));
	philosophers_ring_start(root);
	philosophers_monitor(root);
	philosophers_ring_wait(root);
	philosophers_ring_destroy(root);
	forks_destroy(PROGRAM_SEM_MAIN, forks);
	philosophers_status_sem_destroy();
	return (0);
}

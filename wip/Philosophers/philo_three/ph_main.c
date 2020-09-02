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

char	**g_man_states = (char *[]){
	(char *)"NONE",
	(char *)"is sleeping",
	(char *)"is thinking",
	(char *)"has taken a fork",
	(char *)"is eating",
	(char *)"died"
};

t_param	g_params = { 0 };

sem_t	*g_sem_stdout = SEM_FAILED;

sem_t	*g_sem_forks = SEM_FAILED;
sem_t	*g_sem_grab = SEM_FAILED;
sem_t	*g_sem_stop = SEM_FAILED;
sem_t	*g_sem_wait_start = SEM_FAILED;

sem_t	*g_sem_dead = SEM_FAILED;
sem_t	*g_sem_stop_await = SEM_FAILED;

bool	g_stopped = false;

int
	ph_main(void)
{
	int		err;
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if (!(err = phm_init()))
	{
		if (!(err = ph_table_init(&table)))
			err = ph_sim_start(&table);
		ph_table_destroy(&table);
	}
	phm_destroy();
	return (err);
}

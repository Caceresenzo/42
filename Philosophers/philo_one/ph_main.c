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

t_mutex	g_mutex_stdout = { 0 };
t_mutex	g_mutex_millis = { 0 };

t_mutex	g_mutex_dead = { 0 };

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmm_kill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:11:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:11:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	phmm_kill(t_table *table)
{
	int		index;
	pid_t	pid;

	index = 0;
	while (index < table->child_count)
	{
		if ((pid = table->pids[index]))
			kill(pid, SIGKILL);
		index++;
	}
	return (0);
}

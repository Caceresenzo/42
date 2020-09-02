/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 12:00:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 12:00:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	ph_update(t_man *man, t_state new_state)
{
	long	last;
	char	msg[60];
	size_t	len;

	ft_memset(msg, ' ', sizeof(msg));
	sem_wait(g_sem_stdout);
	if (!g_someone_is_dead)
	{
		last = ph_millis();
		len = ft_sputnbr(msg, last - man->start) + 1;
		len += ft_sputnbr(msg + len, man->id) + 1;
		len += ft_sputstr(msg + len, g_man_states[new_state]);
		msg[len++] = '\n';
		if (new_state == eating)
		{
			sem_wait(man->sem);
			man->last_meal = last;
			sem_post(man->sem);
		}
		write(FD_OUT, msg, len);
		g_someone_is_dead = new_state == dead;
	}
	sem_post(g_sem_stdout);
}

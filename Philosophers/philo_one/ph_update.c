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
	pthread_mutex_lock(&g_mutex_stdout);
	if (!g_someone_is_dead)
	{
		last = ph_millis();
		if (new_state == eating)
		{
			pthread_mutex_lock(&(man->mutex));
			man->last_meal = last;
			pthread_mutex_unlock(&(man->mutex));
		}
		len = ft_sputnbr(msg, last) + 1;
		len += ft_sputnbr(msg + len, man->id) + 1;
		len += ft_sputstr(msg + len, g_man_states[new_state]);
		msg[len++] = '\n';
		write(FD_OUT, msg, len);
		g_someone_is_dead = new_state == dead;
	}
	pthread_mutex_unlock(&g_mutex_stdout);
}

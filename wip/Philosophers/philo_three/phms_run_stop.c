/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phms_run_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:23:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:23:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phms_run_stop(t_seat *seat)
{
	sem_wait(g_sem_stop);
	phms_exit(seat);
}

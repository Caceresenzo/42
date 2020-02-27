/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:55:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 17:55:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	philosophers_status_update(t_man *man, t_man_state new_state)
{
	man->state = new_state;
	x_putnbr(x_millis());
	x_putstr(" ");
	x_putnbr((long)0 + man->id);
	x_putstr(" ");
	x_putstr(g_man_states[new_state]);
	x_putstr("\n");
}

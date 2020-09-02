/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:45:10 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 11:45:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	ph_sleep(int millis)
{
	long end;

	end = ph_millis() + millis;
	while (end > ph_millis())
		usleep(DELAY_SLEEP);
}

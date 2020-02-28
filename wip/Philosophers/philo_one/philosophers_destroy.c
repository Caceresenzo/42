/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:14:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 17:14:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_man
	*philosophers_destroy(t_man *man)
{
	if (man != NULL)
	{
		pthread_detach(man->thr_id);
		free(man);
	}
	return (man = NULL);
}

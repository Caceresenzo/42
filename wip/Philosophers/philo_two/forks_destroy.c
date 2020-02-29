/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:06:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/29 14:06:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t
	*forks_destroy(char *name, sem_t *forks)
{
	if (forks != NULL)
	{
		sem_close(forks);
		sem_unlink(name);
	}
	return (forks = NULL);
}

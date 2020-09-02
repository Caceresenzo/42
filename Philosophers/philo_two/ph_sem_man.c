/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem_man.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:54:38 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/12 13:54:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char
	*name_for_man(char *buffer, int index)
{
	size_t	len;

	len = ft_sputstr(buffer, SM_MAN_PREFIX);
	len += ft_sputnbr(buffer + len, index);
	buffer[len] = '\0';
	return (buffer);
}

sem_t
	*ph_sem_open_man(int index)
{
	char	name[30];

	return (ph_sem_open(name_for_man(name, index), 1));
}

void
	ph_sem_destroy_man(sem_t **sem, int index)
{
	char	name[30];

	ph_sem_destroy(sem, name_for_man(name, index));
}

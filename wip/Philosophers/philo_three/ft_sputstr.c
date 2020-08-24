/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:38:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:38:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t
	ft_sputstr(char *to, char *str)
{
	char	*start;

	start = str;
	while ((*to = *str))
	{
		to++;
		str++;
	}
	return (str - start);
}

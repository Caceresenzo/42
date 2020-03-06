/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:48:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 15:48:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_base_resolve(const char *base, char match)
{
	int	index;

	index = 0;
	while (base[index])
	{
		if (base[index] == match)
			return (index);
		index++;
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:00:52 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 20:00:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isinstr(char c, char *charset)
{
	size_t	index;

	index = 0;
	while (charset[index])
	{
		if (charset[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

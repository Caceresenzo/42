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
	ft_is_base_valid(const char *str)
{
	char	*curr;
	int		index;
	int		jndex;

	curr = (char *)str;
	if (str == NULL || ft_strlen(str) <= 1)
		return (0);
	while (*curr)
	{
		if (ft_iswspace(*curr) || *curr == '+' || *curr == '-')
			return (0);
		curr++;
	}
	index = 0;
	while (index < curr - str)
	{
		jndex = index + 1;
		while (jndex < curr - str)
			if (str[index] == str[jndex++])
				return (0);
		index++;
	}
	return (1);
}

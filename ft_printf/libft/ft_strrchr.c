/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:33:41 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 12:33:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	int		current;
	char	*last;

	index = 0;
	last = NULL;
	while (1)
	{
		current = s[index];
		if (current == c)
			last = (char *)(s + index);
		if (current == '\0')
			break ;
		index++;
	}
	return (last);
}

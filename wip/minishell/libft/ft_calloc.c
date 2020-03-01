/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:54:49 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 19:54:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	size_t	required;

	required = count * size;
	if (!(array = malloc(required)))
		return (NULL);
	ft_memset(array, 0, required);
	return (array);
}

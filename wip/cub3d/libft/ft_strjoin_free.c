/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:25:03 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 16:25:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin_free(char *s1, char *s2, int policy)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (policy != FT_STRJOIN_FREE_DONT)
	{
		if (policy == FT_STRJOIN_FREE_FIRST || policy == FT_STRJOIN_FREE_BOTH)
			free(s1);
		if (policy == FT_STRJOIN_FREE_SECOND || policy == FT_STRJOIN_FREE_BOTH)
			free(s2);
	}
	return (joined);
}

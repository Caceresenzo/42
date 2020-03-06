/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 10:33:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 10:33:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	eval_consume(size_t sub, char **line, size_t *consumed, int ret)
{
	*consumed += sub;
	*line += sub;
	return (ret);
}

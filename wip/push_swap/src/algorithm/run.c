/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:02:22 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:02:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "../../libstack/stack.h"
#include "../push_swap_structs.h"

bool
	algorithm_run(const t_algorithm *algo, t_result *r, t_stack *a, t_stack *b)
{
	return ((*(algo->run))(r, a, b));
}

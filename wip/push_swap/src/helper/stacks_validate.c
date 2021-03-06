/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:24:34 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 13:24:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "../../libstack/stack.h"
#include "../push_swap.h"

bool
	stacks_validate(const t_stack *a, const t_stack *b)
{
	if (!stack_empty(b))
		return (false);
	return (stack_is_sorted(a));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:02:22 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:02:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "../push_swap.h"
#include "../push_swap_structs.h"

const t_algorithm
	*algorithm_storage(void)
{
	static t_algorithm storage[] = {
		{ "smallest", algo_smallest },
		{ "insertion", algo_insertion },
		{ NULL, NULL },
	};

	return (storage);
}

int
	algorithm_storage_size(void)
{
	const t_algorithm *x;

	x = algorithm_storage();
	while (x->name)
		x++;
	return (x - algorithm_storage());
}

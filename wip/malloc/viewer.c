/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:53:30 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 22:53:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "ft.h"

void
show_alloc_mem()
{
	region_t *region = g_region;
	while (region)
	{
		ft_printf("REGION %p (start=%p)\n", region, region_get_start(region));
		ft_printf("  size %l\n", region->size);
		ft_printf("  free_size %l\n", region->free_size);
		ft_printf("  type %s (%d)\n", region_type_to_string(region->type), region->type);

		if (region->type != RT_LARGE)
		{
			block_t *block = region_get_first_block(region);
			while (block)
			{
				ft_printf("  BLOCK %p (start=%p)\n", block, block_get_start(block));
				ft_printf("    size %l\n", block->size);
				ft_printf("    free %b\n", block->free);

				block = block->next;
			}
		}

		region = region->next;
	}
}

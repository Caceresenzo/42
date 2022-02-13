/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 23:59:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/12 23:59:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

const char*
elf_string_get(t_elf *elf, t_elf_section_header *strtab, t_elf_offset offset)
{
	t_elf_offset data_offset;
	t_elf_offset data_size;

	if (!elf || !strtab)
		return (NULL);
	data_offset = elf_section_get_offset(elf, strtab);
	if (!data_offset)
		return (NULL);
	data_size = elf_section_get_size(elf, strtab);
	if (!data_size)
		return (NULL);
	if (offset >= data_size)
		return (NULL);
	return (elf->ptr + data_offset + offset);
}

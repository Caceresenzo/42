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
#include <stdio.h>

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

static bool
elf_string_is_overflowing(t_elf *elf, t_elf_section_header *strtab, t_elf_word offset, const char *str)
{
	const char *end = elf->ptr + elf->size;
	if (str >= end)
		return (true);

	t_elf_word size = elf_section_get_size(elf, strtab) - offset;
	unsigned long distance = end - str;

//	dprintf(2, "size=%u  distance=%lu  MIN=%lu  len=%lu\n", size, distance, MIN(size, distance), ft_strnlen(str, MIN(size, distance)));
	if (ft_strnlen(str, MIN(size, distance)) == (size_t)-1)
		return (true);

	return (false);
}

const char*
elf_string_get_safer(t_elf *elf, t_elf_section_header *strtab, t_elf_word offset)
{
	const char *str = elf_string_get(elf, strtab, offset);

	if (str && elf_string_is_overflowing(elf, strtab, offset, str))
		str = "(null)";

	return (str);
}

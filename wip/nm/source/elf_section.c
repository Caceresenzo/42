/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 22:07:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/12 22:07:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned long
elf_section_sizeof(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (sizeof(Elf32_Shdr));
	if (elf->x64)
		return (sizeof(Elf64_Shdr));
	return (0);
}

t_elf_word
elf_section_get_type(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_type);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_type);
	return (0);
}

t_elf_word
elf_section_get_name(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_name);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_name);
	return (0);
}

t_elf_offset
elf_section_get_offset(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_offset);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_offset);
	return (0);
}

t_elf_word
elf_section_get_size(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_size);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_size);
	return (0);
}

t_elf_word
elf_section_get_entity_size(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_entsize);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_entsize);
	return (0);
}

t_elf_word
elf_section_get_link(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_link);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_link);
	return (0);
}

t_elf_word
elf_section_get_flags(t_elf *elf, t_elf_section_header *section)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section)->sh_flags);
	if (elf->x64)
		return (((Elf64_Shdr*)section)->sh_flags);
	return (0);
}

const char*
elf_section_find_name(t_elf *elf, t_elf_section_header *section)
{
	t_elf_section_header *strings_section = elf_sections_at(elf, elf_header_get_section_string_index(elf));
	if (elf_section_get_type(elf, strings_section) != SHT_STRTAB)
		strings_section = NULL;

	return (elf_string_get_safer(elf, strings_section, elf_section_get_name(elf, section)));
}

t_elf_section_header*
elf_section_next(t_elf *elf, t_elf_section_header *section, t_elf_word n)
{
	if (!elf || !section)
		return (0);
	if (elf->x32)
		return (((Elf32_Shdr*)section) + n);
	if (elf->x64)
		return (((Elf64_Shdr*)section) + n);
	return (0);
}

size_t
sizeof_elf_section(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (sizeof(Elf32_Shdr));
	if (elf->x64)
		return (sizeof(Elf64_Shdr));
	return (0);
}

t_elf_section_header*
elf_sections(t_elf *elf)
{
	t_elf_offset offset;

	if (!elf)
		return (NULL);
	offset = elf_header_get_section_header_offset(elf);
	if (!offset)
		return (NULL);
	return ((void*)(elf->ptr + offset));
}

bool
elf_section_check(t_elf *elf, t_elf_section_header *section)
{
	char *start = section;
	char *end = start + sizeof_elf_section(elf);

	if (!section)
		return (false);
	if (end >= elf->ptr + elf->size)
		return (false);
	if (start <= elf->ptr)
		return (false);
	return (true);
}

t_elf_section_header*
elf_sections_find_by_type(t_elf *elf, t_elf_word type)
{
	t_elf_section_header *section;
	t_elf_half total;

	total = elf_header_get_section_header_number(elf);
	if (!total)
		return (NULL);
	section = elf_sections(elf);
	while (total--)
	{
		if (!elf_section_check(elf, section))
			break;
		if (elf_section_get_type(elf, section) == type)
			return (section);
		section = elf_section_next(elf, section, 1);
	}
	return (NULL);
}

t_elf_section_header*
elf_sections_at(t_elf *elf, t_elf_word index)
{
	t_elf_section_header *section;
	t_elf_half total;

	total = elf_header_get_section_header_number(elf);
	if (!total)
		return (NULL);
	if (index >= total)
		return (NULL);
	section = elf_sections(elf);
	return (elf_section_next(elf, section, index));
}

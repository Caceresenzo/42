/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 22:37:13 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/12 22:37:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned long
elf_symbol_sizeof(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (sizeof(Elf32_Sym));
	if (elf->x64)
		return (sizeof(Elf64_Sym));
	return (0);
}

t_elf_word
elf_symbol_get_name(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (((Elf32_Sym*)symbol)->st_name);
	if (elf->x64)
		return (((Elf64_Sym*)symbol)->st_name);
	return (0);
}

t_elf_address
elf_symbol_get_value(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (((Elf32_Sym*)symbol)->st_value);
	if (elf->x64)
		return (((Elf64_Sym*)symbol)->st_value);
	return (0);
}

t_elf_word
elf_symbol_get_size(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (((Elf32_Sym*)symbol)->st_size);
	if (elf->x64)
		return (((Elf64_Sym*)symbol)->st_size);
	return (0);
}

unsigned char
elf_symbol_get_section_info_bind(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (ELF32_ST_BIND(((Elf32_Sym*)symbol)->st_info));
	if (elf->x64)
		return (ELF64_ST_BIND(((Elf64_Sym*)symbol)->st_info));
	return (0);
}

unsigned char
elf_symbol_get_section_info_type(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (ELF32_ST_TYPE(((Elf32_Sym*)symbol)->st_info));
	if (elf->x64)
		return (ELF64_ST_TYPE(((Elf64_Sym*)symbol)->st_info));
	return (0);
}

unsigned char
elf_symbol_get_section_other_visibility(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (ELF32_ST_VISIBILITY(((Elf32_Sym*)symbol)->st_other));
	if (elf->x64)
		return (ELF32_ST_VISIBILITY(((Elf64_Sym*)symbol)->st_other));
	return (0);
}

t_elf_section
elf_symbol_get_section_index(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (0);
	if (elf->x32)
		return (((Elf32_Sym*)symbol)->st_shndx);
	if (elf->x64)
		return (((Elf64_Sym*)symbol)->st_shndx);
	return (0);
}

t_elf_symbol*
elf_symbol_from(t_elf *elf, t_elf_section_header *section)
{
	t_elf_word size;
	t_elf_word entity_size;
	t_elf_offset offset;

	size = elf_section_get_size(elf, section);
	entity_size = elf_section_get_entity_size(elf, section);
	if (size % entity_size)
		return (NULL);
	offset = elf_section_get_offset(elf, section);
	if (!offset)
		return (NULL);
	if (offset + size > elf->size)
		return (NULL);
	return ((void*)(elf->ptr + offset));
}

t_elf_symbol*
elf_symbol_next(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (((Elf32_Sym*)symbol) + 1);
	if (elf->x64)
		return (((Elf64_Sym*)symbol) + 1);
	return (0);
}

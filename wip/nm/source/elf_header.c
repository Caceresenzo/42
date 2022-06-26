/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 21:32:14 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/12 21:32:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned long
elf_header_sizeof(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (sizeof(Elf32_Ehdr));
	if (elf->x64)
		return (sizeof(Elf64_Ehdr));
	return (0);
}

t_elf_offset
elf_header_get_section_header_offset(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (((Elf32_Ehdr*)elf->ptr)->e_shoff);
	if (elf->x64)
		return (((Elf64_Ehdr*)elf->ptr)->e_shoff);
	return (0);
}

t_elf_half
elf_header_get_section_header_number(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (((Elf32_Ehdr*)elf->ptr)->e_shnum);
	if (elf->x64)
		return (((Elf64_Ehdr*)elf->ptr)->e_shnum);
	return (0);
}

t_elf_half
elf_header_get_section_string_index(t_elf *elf)
{
	if (!elf)
		return (0);
	if (elf->x32)
		return (((Elf32_Ehdr*)elf->ptr)->e_shstrndx);
	if (elf->x64)
		return (((Elf64_Ehdr*)elf->ptr)->e_shstrndx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 21:12:54 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/12 21:12:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <elf.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct
{
	char *ptr;
	off_t size;
	bool x32 :1;
	bool x64 :1;
} t_elf;

typedef void t_elf_header;
typedef void t_elf_section_header;
typedef void t_elf_symbol;
typedef Elf64_Word t_elf_word;
typedef Elf64_Half t_elf_half;
typedef Elf64_Off t_elf_offset;
typedef Elf64_Addr t_elf_address;
typedef Elf64_Section t_elf_section;

unsigned long
elf_header_sizeof(t_elf *elf);

t_elf_offset
elf_header_get_section_header_offset(t_elf *elf);

t_elf_half
elf_header_get_section_header_number(t_elf *elf);

t_elf_half
elf_header_get_section_string_index(t_elf *elf);

unsigned long
elf_section_sizeof(t_elf *elf);

t_elf_word
elf_section_get_type(t_elf *elf, t_elf_section_header *section);

t_elf_word
elf_section_get_name(t_elf *elf, t_elf_section_header *section);

t_elf_offset
elf_section_get_offset(t_elf *elf, t_elf_section_header *section);

t_elf_word
elf_section_get_size(t_elf *elf, t_elf_section_header *section);

t_elf_word
elf_section_get_entity_size(t_elf *elf, t_elf_section_header *section);

t_elf_word
elf_section_get_link(t_elf *elf, t_elf_section_header *section);

t_elf_section_header*
elf_section_next(t_elf *elf, t_elf_section_header *section, t_elf_word n);

t_elf_section_header*
elf_sections(t_elf *elf);

t_elf_section_header*
elf_sections_find_by_type(t_elf *elf, t_elf_word type);

t_elf_section_header*
elf_sections_at(t_elf *elf, t_elf_word index);

unsigned long
elf_symbol_sizeof(t_elf *elf);

t_elf_word
elf_symbol_get_name(t_elf *elf, t_elf_symbol *symbol);

t_elf_address
elf_symbol_get_value(t_elf *elf, t_elf_symbol *symbol);

unsigned char
elf_symbol_get_section_info_bind(t_elf *elf, t_elf_symbol *symbol);

unsigned char
elf_symbol_get_section_info_type(t_elf *elf, t_elf_symbol *symbol);

t_elf_section
elf_symbol_get_section_index(t_elf *elf, t_elf_symbol *symbol);

t_elf_symbol*
elf_symbol_from(t_elf *elf, t_elf_section_header *section);

t_elf_symbol*
elf_symbol_next(t_elf *elf, t_elf_symbol *symbol);

const char*
elf_string_get(t_elf *elf, t_elf_section_header *strtab, t_elf_offset offset);

char
elf_symbol_decode(t_elf *elf, t_elf_symbol *symbol);

#endif

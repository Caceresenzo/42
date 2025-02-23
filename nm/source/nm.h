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
# include "ft.h"

# define NM_VERSION "v1.0"

typedef enum
{
	SORT_NAME = 0,
	SORT_NUMERIC,
	SORT_NONE
} t_sort;

typedef struct
{
	bool help :1;
	bool version :1;
	bool include_all :1;
	bool only_extern :1;
	bool only_undefined :1;
	t_sort sort :2;
	bool sort_reverse;
	char unknown_letter;
	const char *unknown_word;
} t_flags;

typedef struct
{
	bool error;
	const char *text;
} t_message;

typedef struct
{
	t_flags flags;
} t_nm;

typedef void t_elf_header;
typedef void t_elf_section_header;
typedef void t_elf_symbol;
typedef Elf64_Word t_elf_word;
typedef Elf64_Half t_elf_half;
typedef Elf64_Off t_elf_offset;
typedef Elf64_Addr t_elf_address;
typedef Elf64_Section t_elf_section;

typedef struct
{
	char *ptr;
	t_elf_offset size;
	bool x32 :1;
	bool x64 :1;
	t_nm *nm;
} t_elf;

typedef struct
{
	t_elf_address value;
	bool has_value;
	const char *name;
	char letter;
} t_symbol;

int
main_version();

int
main_help(bool is_err);

bool
flags_parse(t_flags *flags, int argc, char **argv, int *file_index);

bool
flags_parse_letter(t_flags *flags, char letter);

bool
flags_parse_word(t_flags *flags, const char *word);

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

t_elf_word
elf_section_get_flags(t_elf *elf, t_elf_section_header *section);

const char*
elf_section_find_name(t_elf *elf, t_elf_section_header *section);

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

t_elf_word
elf_symbol_get_size(t_elf *elf, t_elf_symbol *symbol);

unsigned char
elf_symbol_get_section_info_bind(t_elf *elf, t_elf_symbol *symbol);

unsigned char
elf_symbol_get_section_info_type(t_elf *elf, t_elf_symbol *symbol);

unsigned char
elf_symbol_get_section_other_visibility(t_elf *elf, t_elf_symbol *symbol);

t_elf_section
elf_symbol_get_section_index(t_elf *elf, t_elf_symbol *symbol);

t_elf_symbol*
elf_symbol_from(t_elf *elf, t_elf_section_header *section);

t_elf_symbol*
elf_symbol_next(t_elf *elf, t_elf_symbol *symbol);

const char*
elf_symbol_find_name(t_elf *elf, t_elf_symbol *symbol, t_elf_section_header *symbol_strtab);

const char*
elf_string_get(t_elf *elf, t_elf_section_header *strtab, t_elf_offset offset);

const char*
elf_string_get_safer(t_elf *elf, t_elf_section_header *strtab, t_elf_word offset);

char
elf_symbol_decode(t_elf *elf, t_elf_symbol *symbol);

bool
elf_symbol_is_external(t_elf *elf, t_elf_symbol *symbol);

t_symbol*
symbol_create(t_elf_address value, bool has_value, const char *name, char letter);

void
symbol_print_x64(t_symbol *symbol);

void
symbol_print_x32(t_symbol *symbol);

int
symbol_compare(const t_symbol *left, const t_symbol *right);

int
symbol_list_compare_name(const void *a, const void *b);

int
symbol_list_compare_name_reversed(const void *a, const void *b);

int
symbol_list_compare_numeric(const void *a, const void *b);

int
symbol_list_compare_numeric_reversed(const void *a, const void *b);

t_message
message_simple(const char *text);

t_message
message_error(const char *text);

t_message
message_none(void);

void
debug_print(t_elf *elf, t_elf_symbol *elf_symbol);

#endif

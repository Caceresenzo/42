/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_symbol_decode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:32:56 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 00:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define UNKNOWN_LETTER '?'

struct section_to_type
{
	const char *section;
	char type;
};

/* Map special section names to POSIX/BSD single-character symbol types.
 This table is probably incomplete.  It is sorted for convenience of
 adding entries.  Since it is so short, a linear search is used.  */
static const struct section_to_type stt[] = { //
{ ".drectve", 'i' }, /* MSVC's .drective section */
{ ".edata", 'e' }, /* MSVC's .edata (export) section */
{ ".idata", 'i' }, /* MSVC's .idata (import) section */
{ ".pdata", 'p' }, /* MSVC's .pdata (stack unwind) section */
{ 0, 0 } };

/* Return the single-character symbol type corresponding to
 section S, or '?' for an unknown COFF section.

 Check for leading strings which match, followed by a number, '.',
 or '$' so .idata5 matches the .idata entry.  */

static char
coff_section_type(const char *s)
{
	const struct section_to_type *t;

	for (t = &stt[0]; t->section; t++)
	{
		size_t len = strlen(t->section);
		if (strncmp(s, t->section, len) == 0 && memchr(".$0123456789", s[len], 13) != 0)
			return t->type;
	}

	return UNKNOWN_LETTER;
}

char
elf_symbol_decode_section(t_elf *elf, t_elf_section_header *section)
{
	t_elf_section_header *strings_section = elf_sections_at(elf, elf_header_get_section_string_index(elf));
	if (elf_section_get_type(elf, strings_section) != SHT_STRTAB)
		strings_section = NULL;

	const char *name = elf_string_get(elf, strings_section, elf_section_get_name(elf, section));
	if (!name)
		return (UNKNOWN_LETTER);

	return (coff_section_type(name));
}

bool
startswith(const char *str, const char *prefix)
{
	if (!str)
		return (false);

	return (strncmp(str, prefix, strlen(prefix)) == 0);
}

static char
decode_section_type(t_elf *elf, t_elf_section_header *section)
{
	t_elf_word type = elf_section_get_type(elf, section);
	t_elf_word flags = elf_section_get_flags(elf, section);

	t_elf_section_header *strings_section = elf_sections_at(elf, elf_header_get_section_string_index(elf));
	if (elf_section_get_type(elf, strings_section) != SHT_STRTAB)
		strings_section = NULL;
	const char *name = elf_string_get(elf, strings_section, elf_section_get_name(elf, section));

	bool has_content = type != SHT_NOBITS;
	bool alloc = (flags & SHF_ALLOC) != 0;
	bool load = alloc && type != SHT_NOBITS;
	bool read_only = (flags & SHF_WRITE) == 0;
	bool code = (flags & SHF_EXECINSTR) != 0 || type == SHT_INIT_ARRAY || type == SHT_FINI_ARRAY;
	bool data = !code && load;
	bool small_data = (flags & SHF_MIPS_GPREL) != 0 || startswith(name, ".sbss") || startswith(name, ".sdata");

//	printf("name=%s\n", name);
//	printf("type=%d (%x)\n", type, type);
//
//	printf("flags=");
//	for (unsigned int i = 0; i < sizeof(flags) * 8; ++i)
//		printf("%d", flags & (1 << i));
//	printf("\n");
//
//	printf("has_content=%d\n", has_content);
//	printf("alloc=%d\n", alloc);
//	printf("load=%d\n", load);
//	printf("read_only=%d\n", read_only);
//	printf("code=%d\n", code);
//	printf("data=%d\n", data);
//	printf("small_data=%d\n", small_data);

	if (code)
		return ('t');

	if (data)
	{
		if (read_only)
			return ('r');

		if (small_data)
			return ('g');

		return ('d');
	}

	if (!has_content)
	{
		if (small_data)
			return ('s');

		return ('b');
	}

	bool debugging = startswith(name, ".debug") || startswith(name, ".gnu.debuglto_.debug_") || startswith(name, ".gnu.linkonce.wi.") || startswith(name, ".zdebug") || startswith(name, ".line") || startswith(name, ".stab") || strcmp(name, ".gdb_index") == 0; // TODO
	if (debugging)
		return ('N');

	if (has_content && read_only)
		return ('n');

	return (UNKNOWN_LETTER);
}

static char
do_decode(t_elf *elf, t_elf_symbol *symbol)
{
	t_elf_section section_index = elf_symbol_get_section_index(elf, symbol);
	t_elf_section_header *section = elf_sections_at(elf, section_index);
	unsigned char bind = elf_symbol_get_section_info_bind(elf, symbol);
	unsigned char type = elf_symbol_get_section_info_type(elf, symbol);
//	printf("section_index=%d\n", section_index);

	if (section_index == SHN_MIPS_SCOMMON)
		return ('c');

	if (section_index == SHN_COMMON)
		return ('C');

	if (section_index == SHN_UNDEF)
	{
		if (bind == STB_WEAK)
		{
			if (type == STT_OBJECT)
				return ('v');

			return ('w');
		}

		return ('U');
	}

	// TODO indirect
	if (type == STT_GNU_IFUNC)
		return ('i');

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return ('V');
		else
			return ('W');
	}

	if (bind == STB_GNU_UNIQUE)
		return ('u');

	if (bind != STB_LOCAL && bind != STB_GLOBAL)
		return (UNKNOWN_LETTER);

	char letter;
	if (section_index == SHN_ABS)
		letter = 'a';
	else if (section)
	{
		letter = elf_symbol_decode_section(elf, section);
		if (letter == UNKNOWN_LETTER)
			letter = decode_section_type(elf, section);
	}
	else
		return ('?');

	if (bind == STB_GLOBAL)
		letter = toupper(letter);

	return (letter);
}

char
elf_symbol_decode(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (UNKNOWN_LETTER);

	char letter = do_decode(elf, symbol);

//	unsigned char bind = elf_symbol_get_section_info_bind(elf, symbol);
//
//	if (bind == STB_GLOBAL)
//		return (toupper(letter));
//
//	if (bind == STB_LOCAL)
//		return (tolower(letter));

	return (letter);
}

bool
elf_symbol_is_external(t_elf *elf, t_elf_symbol *symbol)
{
	unsigned char bind = elf_symbol_get_section_info_bind(elf, symbol);

	return (bind == STB_GLOBAL || bind == STB_WEAK);
}

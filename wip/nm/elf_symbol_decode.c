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

/* from: https://github.com/bminor/binutils-gdb/blob/e9c5fe2f40e7da0f104624ee81c9720a7956e64c/bfd/syms.c#L589 */
static char
coff_section_type(const char *name)
{
	if (!name)
		return (UNKNOWN_LETTER);

	struct s_entry
	{
		const char *section;
		char type;
	};

	static const struct s_entry entries[] = { //
	{ ".drectve", 'i' }, /* MSVC's .drective section */
	{ ".edata", 'e' }, /* MSVC's .edata (export) section */
	{ ".idata", 'i' }, /* MSVC's .idata (import) section */
	{ ".pdata", 'p' }, /* MSVC's .pdata (stack unwind) section */
	{ 0, 0 } };

	const struct s_entry *entry;
	for (entry = &entries[0]; entry->section; ++entry)
	{
		size_t len = strlen(entry->section);
		if (strncmp(name, entry->section, len) == 0 && memchr(".$0123456789", name[len], 13) != 0)
			return (entry->type);
	}

	return (UNKNOWN_LETTER);
}

static bool
startswith(const char *str, const char *prefix)
{
	if (!str)
		return (false);

	return (strncmp(str, prefix, strlen(prefix)) == 0);
}

/* from: https://github.com/bminor/binutils-gdb/blob/e9c5fe2f40e7da0f104624ee81c9720a7956e64c/bfd/elf.c#L1087-L1102 */
static bool
is_debugging(const char *name)
{
	static const char *prefixes[] = {
	/**/".debug",
	/**/".gnu.debuglto_.debug_",
	/**/".gnu.linkonce.wi.",
	/**/".zdebug",
	/**/".line",
	/**/".stab" //
	};

	for (unsigned index = 0; index < sizeof(prefixes) / sizeof(prefixes[0]); ++index)
		if (startswith(name, prefixes[index]))
			return (true);

	return (strcmp(name, ".gdb_index") == 0);
}

/* from: https://github.com/bminor/binutils-gdb/blob/e9c5fe2f40e7da0f104624ee81c9720a7956e64c/bfd/syms.c#L612 */
static char
decode_section_type(t_elf *elf, t_elf_section_header *section)
{
	t_elf_word type = elf_section_get_type(elf, section);
	t_elf_word flags = elf_section_get_flags(elf, section);

	const char *name = elf_section_find_name(elf, section);

	bool has_content = type != SHT_NOBITS;
	bool alloc = (flags & SHF_ALLOC) != 0;
	bool load = alloc && type != SHT_NOBITS;
	bool read_only = (flags & SHF_WRITE) == 0;
	bool code = (flags & SHF_EXECINSTR) != 0;
	bool data = !code && load;
	bool small_data = (flags & SHF_MIPS_GPREL) != 0 || startswith(name, ".sbss") || startswith(name, ".sdata");

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

	bool debugging = is_debugging(name);
	if (debugging)
		return ('N');

	if (has_content && read_only)
		return ('n');

	return (UNKNOWN_LETTER);
}

/* from: https://github.com/bminor/binutils-gdb/blob/e9c5fe2f40e7da0f104624ee81c9720a7956e64c/bfd/elf.c#L1006 */
char
elf_symbol_decode(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (UNKNOWN_LETTER);

	t_elf_section section_index = elf_symbol_get_section_index(elf, symbol);
	t_elf_section_header *section = elf_sections_at(elf, section_index);

	unsigned char bind = elf_symbol_get_section_info_bind(elf, symbol);
	unsigned char type = elf_symbol_get_section_info_type(elf, symbol);

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

	// TODO Indirect
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
		letter = coff_section_type(elf_section_find_name(elf, section));
		if (letter == UNKNOWN_LETTER)
			letter = decode_section_type(elf, section);
	}
	else
		return ('?');

	if (bind == STB_GLOBAL)
		letter = toupper(letter);

	return (letter);
}

bool
elf_symbol_is_external(t_elf *elf, t_elf_symbol *symbol)
{
	unsigned char bind = elf_symbol_get_section_info_bind(elf, symbol);

	return (bind == STB_GLOBAL || bind == STB_WEAK);
}

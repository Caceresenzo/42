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

#define UNKNOWN_LETTER '?'

// https://chromium.googlesource.com/chromiumos/third_party/binutils/+/refs/heads/stabilize-falco-4537.91.B/bfd/syms.c#568

typedef struct
{
	const char *section;
	char type;
} t_section_to_type;

static const t_section_to_type g_section_types[] = { //
/**/{ ".drectve", 'i' }, /* MSVC's .drective section */
/**/{ ".edata", 'e' }, /* MSVC's .edata (export) section */
/**/{ ".idata", 'i' }, /* MSVC's .idata (import) section */
/**/{ ".pdata", 'p' }, /* MSVC's .pdata (stack unwind) section */
/**/{ ".bss", 'b' }, //
/**/{ "code", 't' }, /* MRI .text */
/**/{ ".data", 'd' }, //
/**/{ "*DEBUG*", 'N' }, //
/**/{ ".debug", 'N' }, /* MSVC's .debug (non-standard debug syms) */
/**/{ ".drectve", 'i' }, /* MSVC's .drective section */
/**/{ ".edata", 'e' }, /* MSVC's .edata (export) section */
/**/{ ".fini", 't' }, /* ELF fini section */
/**/{ ".idata", 'i' }, /* MSVC's .idata (import) section */
/**/{ ".init", 't' }, /* ELF init section */
/**/{ ".init_array", 't' },
/**/{ ".fini_array", 't' },
/**/{ ".pdata", 'p' }, /* MSVC's .pdata (stack unwind) section */
/**/{ ".rdata", 'r' }, /* Read only data.  */
/**/{ ".rodata", 'r' }, /* Read only data.  */
/**/{ ".sbss", 's' }, /* Small BSS (uninitialized data).  */
/**/{ ".scommon", 'c' }, /* Small common.  */
/**/{ ".sdata", 'g' }, /* Small initialized data.  */
/**/{ ".text", 't' }, //
/**/{ ".comment", 'n' }, //
/**/{ ".dynstr", 'r' }, //
/**/{ ".dynsym", 'r' }, //
/**/{ ".gcc_except_table", 'r' }, //
/**/{ ".gnu", 'r' }, //
/**/{ ".interp", 'r' }, //
/**/{ ".note", 'r' }, //
/**/{ ".plt", 't' }, //
/**/{ ".rel", 'r' }, //
/**/{ ".rela", 'r' }, //
/**/{ "vars", 'd' }, /* MRI .data */
/**/{ "zerovars", 'b' }, /* MRI .bss */
/**/{ ".eh_frame", 'r' }, //
/**/{ ".eh_frame_hdr", 'r' }, //
/**/{ ".dynamic", 'd' }, //
/**/{ ".got", 'd' }, //
/**/{ 0, 0 } //
};

static char
coff_section_type(const char *name)
{
	for (const t_section_to_type *type = &g_section_types[0]; type->section; type++)
	{
		size_t len = strlen(type->section);

		if (!strncmp(name, type->section, len) && memchr(".$0123456789", name[len], 13) != 0)
			return (type->type);
	}

	return (UNKNOWN_LETTER);
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

char
elf_symbol_decode(t_elf *elf, t_elf_symbol *symbol)
{
	if (!elf || !symbol)
		return (UNKNOWN_LETTER);

	unsigned char bind = elf_symbol_get_section_info_bind(elf, symbol);
	unsigned char type = elf_symbol_get_section_info_type(elf, symbol);

	t_elf_section section_index = elf_symbol_get_section_index(elf, symbol);

	if (section_index == SHN_UNDEF)
	{
		if (bind == STB_WEAK)
		{
			if (type == STT_OBJECT)
				return ('v');
			else
				return ('w');
		}
		else
			return ('U');
	}

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			return ('V');
		else
			return ('W');
	}

	if (bind != STB_LOCAL && bind != STB_GLOBAL)
		return (UNKNOWN_LETTER);

	char letter;
	if (section_index == SHN_ABS)
		letter = 'a';
	else
	{
		t_elf_section_header *section = elf_sections_at(elf, section_index);

		if (section)
			letter = elf_symbol_decode_section(elf, section);
		else
			return (UNKNOWN_LETTER);
	}

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
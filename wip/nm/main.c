/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:17:59 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 18:17:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <unistd.h>
#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include "nm.h"

int
main_nm(const char *file, char *ptr, struct stat *statbuf)
{
	if (statbuf->st_size < EI_NIDENT)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: invalid header\n", file);
		return (1);
	}

	if (memcmp(ptr, ELFMAG, 4) != 0)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: invalid magic\n", file);
		return (1);
	}

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;

	if (!is32 && !is64)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: invalid architecture\n", file);
		return (1);
	}

	t_elf elf;
	bzero(&elf, sizeof(t_elf));

	elf.ptr = ptr;
	elf.size = statbuf->st_size;
	elf.x32 = is32;
	elf.x64 = is64;

	if (elf.size < elf_header_sizeof(&elf))
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: invalid header size\n", file);
		return (1);
	}

	t_elf_section_header *symbol_section = elf_sections_find_by_type(&elf, SHT_SYMTAB);
	if (!symbol_section)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: no symbols found\n", file);
		return (1);
	}

	t_elf_word symbol_section_size = elf_section_get_size(&elf, symbol_section);
	t_elf_word symbol_section_entity_size = elf_section_get_entity_size(&elf, symbol_section);
	if (!symbol_section_size || !symbol_section_entity_size)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: 0 symbol\n", file);
		return (1);
	}

	t_elf_word symbol_count = symbol_section_size / symbol_section_entity_size;

	t_elf_symbol *symbol = elf_symbol_from(&elf, symbol_section);
	if (!symbol)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: invalid symbol offset\n", file);
		return (1);
	}

	t_elf_section_header *symbol_strings_section = elf_sections_at(&elf, elf_section_get_link(&elf, symbol_section));
	if (symbol_strings_section && elf_section_get_type(&elf, symbol_strings_section) != SHT_STRTAB)
		symbol_strings_section = NULL;

	while (symbol_count--)
	{
		if (elf_symbol_get_section_index(&elf, symbol) == SHN_ABS)
		{
			symbol = elf_symbol_next(&elf, symbol);
			continue;
		}

		t_elf_word name_offset = elf_symbol_get_name(&elf, symbol);
		if (name_offset)
		{
			const char *name = elf_string_get(&elf, symbol_strings_section, name_offset);

			char letter = elf_symbol_decode(&elf, symbol);

			t_elf_address value = elf_symbol_get_value(&elf, symbol);
			if (value)
				printf("%016lx %c %s\n", (long)value, letter, name);
			else
				printf("%16s %c %s\n", "", letter, name);
		}

		symbol = elf_symbol_next(&elf, symbol);
	}

	return (0);
}

int
main_file(const char *file, bool multiple)
{
	struct stat statbuf;

	int fd = open(file, 0);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, strerror(errno));
		return (1);
	}

	int ret = fstat(fd, &statbuf);
	if (ret == -1)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, strerror(errno));
		close(fd);
		return (1);
	}

	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (!ptr)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, strerror(errno));
		close(fd);
		return (1);
	}

	ret = main_nm(file, ptr, &statbuf);

	munmap(ptr, statbuf.st_size);
	close(fd);
	return (ret);
}

int
main(int argc, char **argv)
{
	t_nm nm;
	bzero(&nm, sizeof(nm));

	int file_index = -1;
	if (!flags_parse(&nm.flags, argc, argv, &file_index))
	{
		if (nm.flags.unknown_word)
			dprintf(STDERR_FILENO, "ft_nm: unrecognized option '--%s'\n", nm.flags.unknown_word);
		else
			dprintf(STDERR_FILENO, "ft_nm: invalid option -- '%c'\n", nm.flags.unknown_letter);

		return (main_help(true));
	}

	if (nm.flags.help)
		return (main_help(false));

	if (nm.flags.version)
		return (main_version());

	if (file_index == -1)
		return (main_file("a.out", false));
	else
	{
		int ret = 0;
		for (int index = file_index; index < argc; index++)
			ret |= main_file(argv[index], argc == 2);
		return (ret);
	}
}

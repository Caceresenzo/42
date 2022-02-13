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
main(int argc, char **argv)
{
	struct stat statbuf;

	int fd = open(argv[1], 0);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "open: %s", strerror(errno));
		return (1);
	}

	int res = fstat(fd, &statbuf);
	if (res == -1)
	{
		dprintf(STDERR_FILENO, "fstat: %s", strerror(errno));
		return (1);
	}

	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (!ptr)
	{
		dprintf(STDERR_FILENO, "mmap: %s", strerror(errno));
		return (1);
	}

	assert(statbuf.st_size > EI_NIDENT);
	assert(memcmp(ptr, ELFMAG, 4) == 0);

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;

	assert(is32 ^ is64);

	t_elf elf;
	bzero(&elf, sizeof(t_elf));

	elf.ptr = ptr;
	elf.size = statbuf.st_size;
	elf.x32 = is32;
	elf.x64 = is64;

	if (statbuf.st_size < elf_header_sizeof(&elf))
	{
		dprintf(STDERR_FILENO, "invalid header size\n");
		return (1);
	}

	t_elf_section_header *symbol_section = elf_sections_find_by_type(&elf, SHT_SYMTAB);
	if (!symbol_section)
	{
		dprintf(STDERR_FILENO, "no symbols found\n");
		return (1);
	}

	t_elf_word symbol_section_size = elf_section_get_size(&elf, symbol_section);
	t_elf_word symbol_section_entity_size = elf_section_get_entity_size(&elf, symbol_section);
	if (!symbol_section_size || !symbol_section_entity_size)
	{
		dprintf(STDERR_FILENO, "0 symbol\n");
		return (1);
	}

	t_elf_word symbol_count = symbol_section_size / symbol_section_entity_size;

	t_elf_symbol *symbol = elf_symbol_from(&elf, symbol_section);
	if (!symbol)
	{
		dprintf(STDERR_FILENO, "invalid symbol offset\n");
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

	munmap(ptr, statbuf.st_size);
	close(fd);
}

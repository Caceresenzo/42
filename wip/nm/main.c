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

// https://chromium.googlesource.com/chromiumos/third_party/binutils/+/refs/heads/stabilize-falco-4537.91.B/bfd/syms.c#568

struct section_to_type
{
	const char *section;
	char type;
};
/* Map section names to POSIX/BSD single-character symbol types.
 This table is probably incomplete.  It is sorted for convenience of
 adding entries.  Since it is so short, a linear search is used.  */
static const struct section_to_type stt[] = { //
{ ".bss", 'b' }, //
{ "code", 't' }, /* MRI .text */
{ ".data", 'd' }, //
{ "*DEBUG*", 'N' }, //
{ ".debug", 'N' }, /* MSVC's .debug (non-standard debug syms) */
{ ".drectve", 'i' }, /* MSVC's .drective section */
{ ".edata", 'e' }, /* MSVC's .edata (export) section */
{ ".fini", 't' }, /* ELF fini section */
{ ".idata", 'i' }, /* MSVC's .idata (import) section */
{ ".init", 't' }, /* ELF init section */
{ ".pdata", 'p' }, /* MSVC's .pdata (stack unwind) section */
{ ".rdata", 'r' }, /* Read only data.  */
{ ".rodata", 'r' }, /* Read only data.  */
{ ".sbss", 's' }, /* Small BSS (uninitialized data).  */
{ ".scommon", 'c' }, /* Small common.  */
{ ".sdata", 'g' }, /* Small initialized data.  */
{ ".text", 't' }, //
{ "vars", 'd' }, /* MRI .data */
{ "zerovars", 'b' }, /* MRI .bss */
{ ".eh_frame", 'r' }, //
{ ".eh_frame_hdr", 'r' }, //
{ ".dynamic", 'd' }, //
{ ".got", 'd' }, //
{ 0, 0 } //
};

static char
coff_section_type(const char *s)
{
	const struct section_to_type *t;
	for (t = &stt[0]; t->section; t++)
		if (!strncmp(s, t->section, strlen(t->section)))
			return t->type;
	return '\0';
}

// https://refspecs.linuxbase.org/elf/gabi4+/ch4.sheader.html
// https://refspecs.linuxbase.org/elf/gabi4+/ch4.symtab.html

#define UNKNOWN_LETTER '?'

char *ptr;
Elf64_Ehdr *header;

char
decode_symbol(Elf64_Sym *symbol, Elf64_Shdr *related)
{
	if (symbol == NULL)
		return UNKNOWN_LETTER;

	int bind = ELF64_ST_BIND(symbol->st_info);
	int type = ELF64_ST_TYPE(symbol->st_info);

	if (symbol->st_shndx == SHN_UNDEF)
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
	if (symbol->st_shndx == SHN_ABS)
		letter = 'a';
	else if (related)
	{
		Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
		Elf64_Shdr *shstr = &sections[header->e_shstrndx];
		char *strtab = (void*)(ptr + shstr->sh_offset);

		const char *name = strtab + related->sh_name;

		letter = coff_section_type(name);
	}
	else
		return (UNKNOWN_LETTER);

	if (bind == STB_GLOBAL)
		letter = toupper(letter);

	return (letter);
}

int
main(int argc, char **argv)
{
	struct stat statbuf;

	int fd = open(argv[1], 0);
	fstat(fd, &statbuf);

	ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

	assert(statbuf.st_size > 4);
	assert(memcmp(ptr, ELFMAG, 4) == 0);

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;
	bool isLsb = ptr[EI_DATA] == ELFDATA2LSB;
	bool isMsb = ptr[EI_DATA] == ELFDATA2MSB;

	assert(is32 ^ is64);
	assert(isLsb ^ isMsb);

	printf("x=%d endian=%s\n", is32 ? 32 : 64, isLsb ? "lsb" : "msb");

	header = (void*)ptr;
	Elf64_Shdr *section_headers = (void*)(ptr + header->e_shoff);
	Elf64_Shdr *symtab = NULL;

	for (int i = 0; i < header->e_shnum; i++)
	{
		Elf64_Shdr *section_header = &section_headers[i];

		if (section_header->sh_type == SHT_SYMTAB)
			symtab = section_header;
	}

	if (symtab)
	{
		Elf64_Sym *sym = (void*)(ptr + symtab->sh_offset);
		Elf64_Sym *sym_end = (void*)(ptr + symtab->sh_offset + symtab->sh_size);

		Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
		Elf64_Shdr *shstr = &sections[symtab->sh_link];
		char *strtab = (void*)(ptr + shstr->sh_offset);

		assert(shstr->sh_type == SHT_STRTAB);

		while (sym != sym_end)
		{
			Elf64_Shdr *related = sym->st_shndx >= SHN_BEFORE ? NULL : &sections[sym->st_shndx];

			char letter = decode_symbol(sym, related);

			if (sym->st_shndx == SHN_ABS)
			{
				sym++;
				continue; // only with -a
			}

			if (sym->st_name)
			{
				if (sym->st_value)
					printf("%016lx %c %s\n", (long)sym->st_value, letter, strtab + sym->st_name);
				else
					printf("%16s %c %s\n", "", letter, strtab + sym->st_name);
			}

			sym++;
		}
	}
}

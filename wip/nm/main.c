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

//#define SHT_NULL	  0
//#define SHT_PROGBITS	  1
//#define SHT_SYMTAB	  2
//#define SHT_STRTAB	  3
//#define SHT_RELA	  4
//#define SHT_HASH	  5
//#define SHT_DYNAMIC	  6
//#define SHT_NOTE	  7
//#define SHT_NOBITS	  8
//#define SHT_REL		  9
//#define SHT_SHLIB	  10
//#define SHT_DYNSYM	  11
//#define SHT_INIT_ARRAY	  14
//#define SHT_FINI_ARRAY	  15
//#define SHT_PREINIT_ARRAY 16
//#define SHT_GROUP	  17
//#define SHT_SYMTAB_SHNDX  18
//#define	SHT_NUM		  19

char const *section_header_names[] = { //
[SHT_NULL] = "SHT_NULL", //
[SHT_PROGBITS] = "SHT_PROGBITS", //
[SHT_SYMTAB] = "SHT_SYMTAB", //
[SHT_STRTAB] = "SHT_STRTAB", //
[SHT_RELA] = "SHT_RELA", //
[SHT_HASH] = "SHT_HASH", //
[SHT_DYNAMIC] = "SHT_DYNAMIC", //
[SHT_NOTE] = "SHT_NOTE", //
[SHT_NOBITS] = "SHT_NOBITS", //
[SHT_REL] = "SHT_REL", //
[SHT_SHLIB] = "SHT_SHLIB", //
[SHT_DYNSYM] = "SHT_DYNSYM", //
[SHT_INIT_ARRAY] = "SHT_INIT_ARRAY", //
[SHT_FINI_ARRAY] = "SHT_FINI_ARRAY", //
[SHT_GROUP] = "SHT_GROUP", //
[SHT_SYMTAB_SHNDX] = "SHT_SYMTAB_SHNDX", //
[SHT_NUM] = "SHT_NUM", //
};

unsigned int
reverse(register unsigned int x)
{
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	return ((x >> 16) | (x << 16));

}

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

int
main(int argc, char **argv)
{
	struct stat statbuf;

	int fd = open(argv[1], 0);
	fstat(fd, &statbuf);

	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

	assert(statbuf.st_size > 4);
	assert(memcmp(ptr, ELFMAG, 4) == 0);

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;
	bool isLsb = ptr[EI_DATA] == ELFDATA2LSB;
	bool isMsb = ptr[EI_DATA] == ELFDATA2MSB;

	assert(is32 ^ is64);
	assert(isLsb ^ isMsb);

	printf("x=%d endian=%s\n", is32 ? 32 : 64, isLsb ? "lsb" : "msb");

	Elf64_Ehdr *header = (void*)ptr;
	Elf64_Shdr *section_headers = (void*)(ptr + header->e_shoff);

	Elf64_Shdr *symtab = NULL;

	for (int i = 0; i < header->e_shnum; i++)
	{
		Elf64_Shdr *section_header = &section_headers[i];

		{
			Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
			Elf64_Shdr *shstr = &sections[header->e_shstrndx];
			char *strtab = (void*)(ptr + shstr->sh_offset);

			const char *type = section_header->sh_type <= SHT_LOOS ? section_header_names[section_header->sh_type] : "???";
			const char *name = strtab + section_header->sh_name;

			printf("%2d | %-20s | %-18s | link=%d\n", i, type, name, section_header->sh_link);
		}

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
			int bind = ELF64_ST_BIND(sym->st_info);
			int type = ELF64_ST_TYPE(sym->st_info);

			char letter = 0;
			bool has_addr = true;

			Elf64_Shdr *related = sym->st_shndx >= SHN_BEFORE ? NULL : &sections[sym->st_shndx];

			if (sym->st_shndx == SHN_ABS)
			{
				letter = 'a';
				sym++;
				continue; // only with -a
			}
			else if (sym->st_shndx == SHN_COMMON)
				letter = 'c';
			else if (sym->st_shndx == SHN_UNDEF)
			{
				has_addr = false;
				letter = 'u';
			}
			else if (related)
			{
				Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
				Elf64_Shdr *shstr = &sections[header->e_shstrndx];
				char *strtab = (void*)(ptr + shstr->sh_offset);

				const char *name = strtab + related->sh_name;

				letter = coff_section_type(name);
			}

			if (bind == STB_GLOBAL)
				letter = toupper(letter);
			else if (bind == STB_LOCAL)
				letter = tolower(letter);
			else if (bind == STB_WEAK)
				letter = 'w';

			if (letter == 0)
				letter = '?';

			if (sym->st_name)
			{
				if (has_addr)
					printf("%016lx %c %s    %x\n", (long)sym->st_value, letter, strtab + sym->st_name, type);
				else
					printf("%16s %c %s     %x\n", "", letter, strtab + sym->st_name, type);
			}

			sym++;
		}
	}
}

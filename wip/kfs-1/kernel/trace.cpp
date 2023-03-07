#include <types.h>
#include <kernel/trace.hpp>
#include <elf.h>
#include <string.h>
#include <multiboot.h>
#include <cpu/multiboot.hpp>

struct stackframe
{
		struct stackframe *ebp;
		uint32_t eip;
};

static int consume_int(char **input)
{
	int result = 0;

	char c;
	while ((c = **input))
	{
		if (c >= '0' && c <= '9')
		{
			result *= 10;
			result += c - '0';
		}
		else
			break;

		*input += 1;
	}

	return (result);
}

static char* demangle_name(char *mangled)
{
	if (mangled == NULL || mangled[0] != '_' || mangled[1] != 'Z')
		return (mangled);

	char *start = mangled;

	char buffer[128];
	char *head = buffer;

	// skip leading '_Z'
	mangled += 2;

	while (*mangled)
	{
		if (*mangled == 'N')
			++mangled;
		else if (*mangled >= '0' && *mangled <= '9')
		{
			int length = consume_int(&mangled);
			memcpy(head, mangled, length);
			head += length;
			mangled += length;

			if (*mangled != 'E')
			{
				memcpy(head, "::", 2);
				head += 2;
			}
		}
		else
		{
			break;
		}
	}

	*head = '\0';
	memcpy(start, buffer, strlen(buffer) + 1);

	return (start);
}

kfs::trace::symbol_t kfs::trace::get_symbol(void *frame)
{
	static symbol_t empty = { };

	Elf32_Shdr *symtab_section_header = NULL;

	const multiboot_info_t *mbi = kfs::multiboot::get();

	if ((mbi->flags & MULTIBOOT_INFO_ELF_SHDR) == 0)
		return (empty);

	multiboot_elf_section_header_table_t *shdr_table = (multiboot_elf_section_header_table_t*)&mbi->u.elf_sec;

	char *strtab = NULL;
	Elf32_Sym *symtab = NULL;
	unsigned int symbol_count = 0;

	for (int index = 0; index < shdr_table->num; index++)
	{
		Elf32_Shdr *shdr = (Elf32_Shdr*)(shdr_table->addr + index * shdr_table->size);

		if (shdr->sh_type == SHT_SYMTAB)
		{
			symtab = (Elf32_Sym*)shdr->sh_addr;
			symbol_count = shdr->sh_size / shdr->sh_entsize;

			Elf32_Shdr *strtab_shdr = (Elf32_Shdr*)(shdr_table->addr + shdr->sh_link * shdr_table->size);
			strtab = (char*)strtab_shdr->sh_addr;

			break;
		}
	}

	if (!symtab || !strtab)
		return (empty);

	for (int index = 0; index < symbol_count; index++)
	{
		Elf32_Sym symbol = symtab[index];
		if (ELF32_ST_TYPE(symbol.st_info) != STT_FUNC)
			continue;

		uint32_t start = symbol.st_value;
		uint32_t end = start + symbol.st_size;

		if (start == end)
			continue;

		if ((void*)start <= frame && (void*)end >= frame)
		{
			symbol_t result = {
				start,
				end,
				""
			};

			if (strtab)
			{
				const char *name = strtab + symbol.st_name;
				strcpy(result.name, name);
				demangle_name(result.name);
			}

			return (result);
		}
	}

	return (empty);
}

int kfs::trace::backtrace(void **buffer, int size)
{
	struct stackframe *stk;
	asm ("movl %%ebp,%0" : "=r"(stk) ::);

	int32_t frame;
	for (frame = 0; stk && frame < size; ++frame)
	{
		buffer[frame] = (void*)stk->eip;
		stk = stk->ebp;
	}

	return (frame);
}

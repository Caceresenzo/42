#include <types.h>
#include <kernel/trace.hpp>

struct stackframe
{
		struct stackframe *ebp;
		uint32_t eip;
};

kfs::trace::symbol_t kfs::trace::get_symbol(void *frame)
{
	for (symbol_t *symbol = symbols_table; symbol->name; ++symbol)
	{
		if ((void*)symbol->start <= frame && (void*)symbol->end >= frame)
			return (*symbol);
	}

	static symbol_t empty = { };
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

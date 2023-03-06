#include <types.h>
#include <kernel/trace.hpp>

struct stackframe
{
		struct stackframe *ebp;
		uint32_t eip;
};

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

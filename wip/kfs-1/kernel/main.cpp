#include <kernel/trace.hpp>
#include <drivers/vga.hpp>
#include <drivers/timer.hpp>
#include <drivers/keyboard.hpp>
#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/pit.hpp>
#include <cpu/io.hpp>
#include <cpu/interrupt.hpp>
#include <cpu/multiboot.hpp>
#include <string.h>
#include <stdio.h>
#include <multiboot.h>

void lolwrite(const char *str)
{
	static enum kfs::vga::color colors[] = {
		kfs::vga::color::COLOR_LIGHT_BLUE,
		kfs::vga::color::COLOR_LIGHT_GREEN,
		kfs::vga::color::COLOR_LIGHT_CYAN,
		kfs::vga::color::COLOR_LIGHT_RED,
		kfs::vga::color::COLOR_LIGHT_MAGENTA,
	};

	uint32_t line = 0;
	uint32_t offset = 0;

	uint8_t previous_color = kfs::vga::get_color();

	char c;
	while ((c = *str))
	{
		if (c == '\n')
		{
			++line;
			offset = line * 2;
		}
		else
			++offset;

		enum kfs::vga::color fore = colors[(offset / 8) % countof(colors)];
		kfs::vga::set_color((enum kfs::vga::color)fore, kfs::vga::COLOR_BLACK);

		kfs::vga::put(c);
		str++;
	}

	kfs::vga::set_color(previous_color);
}

extern "C"
{
	extern uint32_t _stack_bottom;
	extern uint32_t _stack_top;
}

namespace shell
{
	typedef struct
	{
			const char *name;
			void (*function)(void);
	} command_t;

	char buffer[32] = { 0 };
	bool running = false;

	void do_ft();
	void do_tick();
	void do_cpuid();
	void do_reboot();
	void do_shutdown();
	void do_multiboot();
	void do_halt();
	void do_exit();
	void do_trace();
	void do_stack();
	void do_help();

	command_t commands[] = {
		{ .name = "42", .function = do_ft },
		{ .name = "ft", .function = do_ft },
		{ .name = "tick", .function = do_tick },
		{ .name = "cpuid", .function = do_cpuid },
		{ .name = "reboot", .function = do_reboot },
		{ .name = "shutdown", .function = do_shutdown },
		{ .name = "multiboot", .function = do_multiboot },
		{ .name = "halt", .function = do_halt },
		{ .name = "exit", .function = do_exit },
		{ .name = "trace", .function = do_trace },
		{ .name = "stack", .function = do_stack },
		{ .name = "help", .function = do_help },
		{ 0, 0 },
	};

	void do_ft()
	{
		lolwrite("\n"
			"     d8888   .d8888b.       888       .d888          \n"
			"    d8P888  d88P  Y88b      888      d88P\"           \n"
			"   d8P 888         888      888      888             \n"
			"  d8P  888       .d88P      888  888 888888 .d8888b  \n"
			" d88   888   .od888P\"       888 .88P 888    88K      \n"
			" 8888888888 d88P\"           888888K  888    \"Y8888b. \n"
			"       888  888\"            888 \"88b 888         X88 \n"
			"       888  888888888       888  888 888     88888P' \n"
			"\n"
			);
	}

	void do_tick()
	{
		printk("%d\n", kfs::timer::tick_count());
	}

	void do_cpuid()
	{
		char buffer[20];
		uint32_t eax;
		uint32_t ebx;
		uint32_t ecx;
		uint32_t edx;

		if (kfs::io::cpuid(kfs::io::cpuid_requests::CPUID_GETVENDORSTRING, buffer))
			printk("vendor:           %s\n", buffer);

		kfs::io::cpuid(kfs::io::cpuid_requests::CPUID_GETFEATURES, &eax, &ebx, &ecx, &edx);
		{
			printk("stepping:         %d\n", eax & 0xF);
			printk("model:            %d\n", (eax >> 4) & 0xF);
			printk("family:           %d\n", (eax >> 8) & 0xF);
			printk("processor type:   %d\n", (eax >> 12) & 0x3);
			printk("extended model:   %d\n", (eax >> 16) & 0xF);
			printk("extended family:  %d\n", (eax >> 20) & 0xFF);
		}
	}

	void do_reboot()
	{
		printk("see you!\n");
		kfs::io::reboot();
	}

	void do_shutdown()
	{
		printk("good bye!\n");
		kfs::io::shutdown();
	}

	void do_multiboot()
	{
		kfs::multiboot::dump();
	}

	void do_halt()
	{
		printk("halted!\n");
		kfs::io::halt();
	}

	void do_exit()
	{
		kfs::io::shutdown();
	}

	void do_help()
	{
		for (command_t *command = commands; command->name; ++command)
			printk("%s ", command->name);

		printk("\n");
	}

	void do_trace()
	{
		void *frames[25];
		int32_t frame_count = kfs::trace::backtrace(frames, countof(frames));

		printk("Stack Trace:\n");
		for (int32_t index = 0; index < frame_count; ++index)
		{
			void *frame = frames[index];
			kfs::trace::symbol_t symbol = kfs::trace::get_symbol(frame);

			if (symbol.name[0])
			{
				int32_t offset = (int32_t)frame - symbol.start;
				printk("%d - 0x%x - %s+%d\n", index, frame, symbol.name, offset);
			}
			else
				printk("%d - 0x%x - ??\n", index, frame);
		}
	}

	void do_stack()
	{
		uint32_t bottom = (uint32_t)&_stack_bottom;
		uint32_t top = (uint32_t)&_stack_top;

		if (bottom > top)
		{
			uint32_t tmp = bottom;
			bottom = top;
			top = tmp;
		}

		uint32_t align = 16;
		uint8_t last[align] = { 0 };
		memset(last, 0, align);
		bool same = false;

		uint32_t line = 0;
		for (uint32_t addr = bottom; addr <= top; addr += align)
		{
			if (addr != bottom && memcmp((void*)last, (void*)addr, align) == 0)
			{
				if (!same)
				{
					same = true;
					printk("*\n");
					line += 1;
				}

				continue;
			}
			else
				same = false;

			memcpy(last, (void*)addr, align);

			if (line > 20)
				kfs::keyboard::wait();

			printk("%p  ", addr);

			for (uint32_t offset = 0; offset < align; ++offset)
			{
				if (offset == 8)
					printk(" ");

				uint8_t value = *(uint8_t*)(addr + offset);

				if (value < 0x10)
					printk("0");
				printk("%x ", value);
			}

			printk(" |");
			for (uint32_t offset = 0; offset < align; ++offset)
			{
				uint8_t value = *(uint8_t*)(addr + offset);

				if (!isprint(value))
					value = '.';

				printk("%c", value);
			}
			printk("|");

			printk("\n");
			line += 1;
		}
	}

	void execute(const char *line)
	{
		for (command_t *command = commands; command->name; ++command)
		{
			if (strcmp(command->name, line) == 0)
			{
				running = true;
				command->function();
				running = false;
				return;
			}
		}

		printk("unknown command\n");
	}

	void prompt()
	{
		putstr("$> ");
	}

	void callback(kfs::keyboard::key_t key)
	{
		if (running)
			return;

		if (key.letter == '\e')
		{
			do_shutdown();
			return;
		}

		uint8_t letter = key.letter;
		if (!letter || !key.state)
			return;

		uint32_t len = strlen(buffer);

		if (letter == '\r')
		{
			putchar('\n');

			if (buffer[0])
			{
				execute(buffer);
				memset(buffer, 0, sizeof(buffer));
			}

			prompt();
			return;
		}

		bool is_backspace = letter == '\b';

		if (!is_backspace && len + 1 != countof(buffer))
		{
			buffer[len] = letter;
			putchar(letter);
		}

		if (is_backspace && len != 0)
		{
			buffer[len - 1] = '\0';
			putstr("\b \b");
		}

		kfs::vga::move_cursor();
	}

	void initialize()
	{
		kfs::keyboard::set_callback(&callback);
		prompt();
	}
}

extern "C"
{
	void kmain(unsigned long magic, unsigned long addr)
	{
		kfs::io::cli();

		kfs::vga::initialize();
		kfs::gdt::initialize();
		kfs::idt::initialize();
		kfs::interrupt::initialize();

		kfs::timer::initialize();
		kfs::keyboard::initialize();

		if (!kfs::multiboot::initialize(magic, addr))
			return;

		kfs::io::sti();

		shell::do_ft();
		shell::initialize();

		while (1)
			kfs::io::halt();
	}
}

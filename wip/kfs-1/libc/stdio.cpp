#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <types.h>
#include <drivers/vga.hpp>

void putchar(char c)
{
	kfs::vga::put(c);
}

void putstr(const char *str)
{
	kfs::vga::write(str);
}

void putnbr(int32_t n)
{
	putnbrr(n, 10);
}

void putnbrr(int32_t n, uint8_t radix)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}

	char buffer[20] = { 0 };
	char *end = buffer + sizeof(buffer) - 2;

	do
	{
		*end = "0123456789abcdef"[n % radix];
		--end;
		n /= radix;
	}
	while (n);

	putstr(end + 1);
}

void putunbr(uint32_t n)
{
	putunbrr(n, 10);
}

void putunbrr(uint32_t n, uint8_t radix)
{
	char buffer[20] = { 0 };
	char *end = buffer + sizeof(buffer) - 2;

	do
	{
		*end = "0123456789abcdef"[n % radix];
		--end;
		n /= radix;
	}
	while (n);

	putstr(end + 1);
}

//#ifndef va_list
//# define va_list void*
//#endif
//
//#ifndef va_start
//# define va_start(list, last_arg)
//#endif
//
//#ifndef va_end
//# define va_end(list)
//#endif
//
//#ifndef va_arg
//# define va_arg(list, type) ((type)0)
//#endif

void printk(const char *format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	while (true)
	{
		char c = *format++;
		if (!c)
			return;

		if (c != '%')
		{
			putchar(c);
			continue;
		}

		c = *format++;
		if (!c)
			return;

		if (c == 'd')
		{
			int32_t i = va_arg(parameters, int32_t);
			putnbr(i);
			continue;
		}

		if (c == 'u')
		{
			uint32_t i = va_arg(parameters, uint32_t);
			putunbr(i);
			continue;
		}

		if (c == 'b')
		{
			uint32_t i = va_arg(parameters, uint32_t);
			putunbrr(i, 2);
			continue;
		}

		if (c == 'x')
		{
			int32_t i = va_arg(parameters, int32_t);
			putunbrr(i, 16);
			continue;
		}

		if (c == 'x')
		{
			void *p = va_arg(parameters, void*);
			putstr("0x");
			putunbrr((uint64_t)p, 16);
			continue;
		}

		if (c == 's')
		{
			const char *str = va_arg(parameters, char*);
			if (!str)
				str = "(null)";
			putstr (str);
			continue;
		}

		putchar('%');
		putchar(c);
		// TODO Unknown specified
	}
}

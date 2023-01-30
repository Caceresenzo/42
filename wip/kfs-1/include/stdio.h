#ifndef STDIO_H
# define STDIO_H

# include <types.h>

#define countof(arr) (sizeof(arr) / sizeof(arr[0]))

#ifdef __cplusplus
extern "C"
{
#endif

	void putchar(char c);
	void putstr(const char *str);
	void putnbr(int32_t n);
	void putnbrr(int32_t n, uint8_t radix);
	void putunbr(uint32_t n);
	void putunbrr(uint32_t n, uint8_t radix);
	void printk(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif

#ifndef STRING_H
# define STRING_H

# include <types.h>

# ifndef countof
#  define countof(arr) (sizeof(arr) / sizeof(arr[0]))
# endif

# ifndef NULL
#  define NULL (0)
# endif

#ifdef __cplusplus
extern "C"
{
#endif

	uint32_t strlen(const char *str);
	char* strcpy(char *dest, const char *src);
	void* memmove(void *dest, const void *src, uint32_t n);

#ifdef __cplusplus
}
#endif

#endif

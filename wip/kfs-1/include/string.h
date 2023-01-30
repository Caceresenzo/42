#ifndef STRING_H
# define STRING_H

# include <types.h>

#define countof(arr) (sizeof(arr) / sizeof(arr[0]))

#ifdef __cplusplus
extern "C"
{
#endif


	uint32_t strlen(const char *str);
	void* memmove(void *dest, const void *src, uint32_t n);

#ifdef __cplusplus
}
#endif

#endif

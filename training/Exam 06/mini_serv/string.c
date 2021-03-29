#include <stdlib.h>
#include <string.h>

#include "mini_serv.h"

t_instanced_string*
istr_wrap(char *cstr)
{
	t_instanced_string *str = (t_instanced_string*)malloc(sizeof(t_instanced_string));

	if (str)
	{
		str->use = 0;
		str->data = strdup(cstr);

		if (str->data)
			str->len = strlen(cstr);
		else
		{
			free(str);
			str = NULL;
		}
	}

	return (str);
}

t_instanced_string*
istr_use(t_instanced_string *str)
{
	++str->use;
	return (str);
}

void
istr_unuse(t_instanced_string *str)
{
	if (--str->use == 0)
	{
		free(str->data);
		free(str);
	}
}

void
istr_unuse_v(void *str)
{
	istr_unuse((t_instanced_string*)str);
}


#include <debug.h>

#include "srealloc.h"

void* srealloc(void* old, size_t size)
{
	void* new = realloc(old, size);
	if (!new)
	{
		fprintf(stderr, "%s: realloc(): %m\n", argv0);
		exit(e_syscall_failed);
	}
	return new;
}


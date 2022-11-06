
#include <stdio.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

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


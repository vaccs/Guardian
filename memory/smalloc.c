
#include <stdio.h>
#include <stdlib.h>

#include <debug.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include "smalloc.h"

void* smalloc(size_t size)
{
	void* ptr = malloc(size);
	if (!ptr)
	{
		fprintf(stderr, "%s: malloc(size = %lu): %m\n", argv0, size);
		exit(e_syscall_failed);
	}
	return ptr;
}


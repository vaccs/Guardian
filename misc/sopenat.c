
#include <debug.h>

#include <stdio.h>
#include <fcntl.h>

#include <stdlib.h>

#include <enums/error.h>

#include "sopenat.h"

int sopenat(int dirfd, const char* path, int flags)
{
	int fd = openat(dirfd, path, flags);
	
	if (fd < 0)
	{
		fprintf(stderr, "guardian: open(\"%s\"): %m\n", path),
		exit(e_syscall_failed);
	}
	
	return fd;
}


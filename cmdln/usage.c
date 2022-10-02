
#include <stdio.h>
#include <stdlib.h>

#include <defines/argv0.h>

#include "usage.h"

void usage(int code)
{
	printf("usage: %s -i <path/to/input>.maia -o <path/to/outout.c>\n", argv0);
	exit(code);
}



#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_funcdata(const void* a, const void* b)
{
	const struct funcdata *A = a, *B = b;
	
	if (A->type > B->type)
		return +1;
	else if (A->type < B->type)
		return -1;
	else if (A->kind > B->kind)
		return +1;
	else if (A->kind < B->kind)
		return -1;
	else
		return +0;
}


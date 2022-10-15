
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_funcdata(const void* a, const void* b)
{
	const struct funcdata *A = a, *B = b;
	
	if (A->kind > B->kind)
		return +1;
	else if (A->kind < B->kind)
		return -1;
	else switch (A->kind)
	{
		case fk_lambda_new:
			TODO;
			break;
		
		case fk_new:
		case fk_inc:
		case fk_compare:
		case fk_index:
		case fk_free:
			if (A->type > B->type)
				return +1;
			else if (A->type < B->type)
				return -1;
			break;
	}
	
	return +0;
}


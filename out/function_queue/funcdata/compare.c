
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
		case fk_new:
		case fk_inc:
		case fk_compare:
		case fk_index:
		case fk_free:
			if (A->type > B->type)
				return +1;
			else if (A->type < B->type)
				return -1;
			else
				return +0;
		
		case fk_lambda_new:
		case fk_lambda_evaluate:
		case fk_lambda_free:
			if (A->lexpression < B->lexpression)
				return -1;
			else if (A->lexpression > B->lexpression)
				return +1;
			else if (A->lvalue < B->lvalue)
			{
				TODO;
			}
			else if (A->lvalue > B->lvalue)
			{
				TODO;
			}
			else
				return +0;
		
		default:
			TODO;
			break;
	}
}


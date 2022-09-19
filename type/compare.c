
#include <debug.h>

#include "struct.h"
#include "compare.h"

#include "grammar/compare.h"

int compare_types(const void* a, const void* b)
{
	int cmp;
	const struct type *A = a, *B = b;
	ENTER;
	
	dpv(A->kind);
	dpv(B->kind);
	
	if (A->kind < B->kind)
	{
		TODO;
	}
	else if (A->kind > B->kind)
	{
		TODO;
	}
	else switch (A->kind)
	{
		case tk_grammar:
			cmp = compare_grammar_types(
				(struct grammar_type*) A,
				(struct grammar_type*) B);
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return cmp;
}


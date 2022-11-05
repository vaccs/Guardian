
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"
#include "inheritance.h"

int compare_types(const void* a, const void* b)
{
	int cmp;
	const struct type *A = a, *B = b;
	ENTER;
	
	dpv(A->kind);
	dpv(B->kind);
	
	if (A->kind < B->kind)
	{
		cmp = -1;
	}
	else if (A->kind > B->kind)
	{
		cmp = +1;
	}
	else
	{
		dpv(B);
		dpv(B->inheritance);
		
		assert(B->inheritance->compare);
		
		cmp = (B->inheritance->compare)(A, B);
	}
	
	EXIT;
	return cmp;
}

















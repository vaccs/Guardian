
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "compare.h"

int compare_values(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	dpv(a->kind);
	
	assert(a->kind == b->kind);
	
	assert(a->inheritance);
	assert(a->inheritance->compare);
	
	int cmp = (a->inheritance->compare)(a, b);
	
	EXIT;
	return cmp;
}


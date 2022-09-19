
#include <debug.h>

#include <yacc/structinfo/compare.h>

#include "struct.h"
#include "compare.h"

int compare_grammar_types(
	const struct grammar_type* a,
	const struct grammar_type* b)
{
	ENTER;
	
	int cmp = compare_structinfos(a->structinfo, b->structinfo);
	
	EXIT;
	return cmp;
}


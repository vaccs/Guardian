
#include <debug.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_grammar_type(
	struct type* super)
{
	ENTER;
	
	struct grammar_type* this = (void*) super;
	
	free_structinfo(this->structinfo);
	
	EXIT;
}


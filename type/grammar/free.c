
#include <debug.h>

#include <string/free.h>

#include <list/named_type/free.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_grammar_type(
	struct type* super)
{
	ENTER;
	
	struct grammar_type* this = (void*) super;
	
	free_string(this->name);
	
	free_named_type_list(this->fields);
	
	EXIT;
}


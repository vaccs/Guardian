
#include <debug.h>

#include <gegex/free.h>

#include "struct.h"
#include "free.h"

void free_named_grammar(void* ptr)
{
	ENTER;
	
	struct named_grammar* this = ptr;
	
	free_string(this->name);
	
	free_gegex(this->grammar);
	
	free(this);
	
	EXIT;
}


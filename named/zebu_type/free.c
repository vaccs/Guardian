
#include <stdlib.h>

#include <debug.h>

#include <string/free.h>

#include <parse/parse.h>

#include "struct.h"
#include "free.h"

void free_named_zebu_type(void* ptr)
{
	ENTER;
	
	struct named_zebu_type* this = ptr;
	
	free_string(this->name);
	
	free_zebu_type(this->type);
	
	free(this);
	
	EXIT;
}


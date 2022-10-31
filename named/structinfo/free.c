
#include <debug.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_named_structinfo(void* ptr)
{
	struct named_structinfo* this = ptr;
	
	free_string(this->name);
	
	free_structinfo(this->structinfo);
	
	free(this);
}


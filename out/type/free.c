
#include <debug.h>

#include <stringtree/free.h>

#include <set/ptr/free.h>

#include "struct.h"
#include "free.h"

void free_out_type(
	struct out_type* this)
{
	ENTER;
	
	free_ptrset(this->dependent_on);
	
	free_ptrset(this->dependent_of);
	
	free_stringtree(this->text);
	
	free(this);
	
	EXIT;
}


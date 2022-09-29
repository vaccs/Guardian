
#include <debug.h>

#include <yacc/structinfo/free.h>

#include "struct.h"
#include "free.h"

void free_gegex_transition(struct gegex_transition* this)
{
	ENTER;
	
	free_structinfo(this->structinfo);
	
	free(this);
	
	EXIT;
}


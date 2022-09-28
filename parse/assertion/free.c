
#include <debug.h>

#include "../parse.h"

#include "struct.h"
#include "free.h"

void free_raw_assertion(
	struct raw_assertion* this)
{
	ENTER;
	
	free_zebu_expression(this->expression);
	
	free(this);
	
	EXIT;
}


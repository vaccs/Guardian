
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct expressionset* new_expressionset()
{
	ENTER;
	
	struct expressionset* this = smalloc(sizeof(*this));
	
	EXIT;
	return this;
}


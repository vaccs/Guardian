
#include <debug.h>

#include "struct.h"
#include "submit.h"

void subtype_queue_submit(
	struct subtype_queue* this,
	struct lambda_expression* lexpression)
{
	ENTER;
	
	if (ptrset_add(this->queued, lexpression))
		quack_append(this->todo, lexpression);
	
	EXIT;
}


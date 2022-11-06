
#include <debug.h>

#include <set/ptr/add.h>

#include <quack/append.h>

#include "struct.h"
#include "submit.h"

void type_queue_submit(
	struct type_queue* this,
	struct type* type)
{
	ENTER;
	
	if (ptrset_add(this->queued, type))
	{
		quack_append(this->todo, type);
	}
	
	EXIT;
}



#include <debug.h>

#include "struct.h"
#include "submit.h"

void set_queue_submit(
	struct set_queue* this,
	struct string* name)
{
	ENTER;
	
	if (stringset_add(this->queued, name))
	{
		quack_append(this->todo, name);
	}
	
	EXIT;
}


#include <debug.h>

#include <set/ptr/new.h>

#include <quack/new.h>

#include "struct.h"
#include "new.h"

struct subtype_queue* new_subtype_queue()
{
	ENTER;
	
	struct subtype_queue* this = smalloc(sizeof(*this));
	
	this->todo = new_quack();
	
	this->queued = new_ptrset();
	this->done = new_ptrset();
	
	this->text = NULL;
	
	EXIT;
	return this;
}



#include <debug.h>

#include <memory/smalloc.h>

#include <set/ptr/new.h>

#include <quack/new.h>

#include "struct.h"
#include "new.h"

struct type_queue* new_type_queue()
{
	ENTER;
	
	struct type_queue* this = smalloc(sizeof(*this));
	
	this->todo = new_quack();
	
	this->queued = new_ptrset();
	this->done = new_ptrset();
	
	this->text = NULL;
	
	EXIT;
	return this;
}


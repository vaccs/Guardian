
#include <debug.h>

#include <memory/smalloc.h>

#include <set/ptr/new.h>

#include <quack/new.h>

#include "struct.h"
#include "new.h"

struct subtype_queue* new_subtype_queue()
{
	ENTER;
	
	struct subtype_queue* this = smalloc(sizeof(*this));
	
	this->values.todo = new_quack();
	this->values.queued = new_ptrset();
	this->values.done = new_ptrset();
	
	this->expressions.todo = new_quack();
	this->expressions.queued = new_ptrset();
	this->expressions.done = new_ptrset();
	
	this->text = NULL;
	
	EXIT;
	return this;
}


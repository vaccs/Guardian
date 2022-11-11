
#include <debug.h>

#include <memory/smalloc.h>

#include <quack/new.h>

#include <set/string/new.h>

#include "struct.h"
#include "new.h"

struct declare_queue* new_declare_queue()
{
	ENTER;
	
	struct declare_queue* this = smalloc(sizeof(*this));
	
	this->todo = new_quack();
	
	this->queued = new_stringset();
	this->done = new_stringset();
	
	this->text = NULL;
	
	EXIT;
	return this;
}


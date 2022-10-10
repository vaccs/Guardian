
#include <debug.h>

#include "struct.h"
#include "new.h"

struct declare_queue* new_declare_queue()
{
	ENTER;
	
	struct declare_queue* this = smalloc(sizeof(*this));
	
	this->todo = new_quack();
	
	this->queued = new_stringset();
	
	this->init_text = NULL;
	this->uninit_text = NULL;
	
	EXIT;
	return this;
}


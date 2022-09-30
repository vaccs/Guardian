
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print.h"

void type_print(
	struct type* this)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print);
	
	(this->inheritance->print)(this);
	
	EXIT;
}


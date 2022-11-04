
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print.h"

void value_print(
	struct value* this)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print);
	
	(this->inheritance->print)(this);
	
	EXIT;
}


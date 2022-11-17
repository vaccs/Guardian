
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print.h"

struct stringtree* value_print(
	struct value* this)
{
	ENTER;
	
	TODO;
	#if 0
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print);
	
	(this->inheritance->print)(this);
	#endif
	
	EXIT;
}


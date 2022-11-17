
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print.h"

struct stringtree* value_print2(
	struct value* this)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print);
	
	struct stringtree* tree = (this->inheritance->print)(this);
	
	EXIT;
	return tree;
}


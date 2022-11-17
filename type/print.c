
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print.h"

struct stringtree* type_print2(
	struct type* this)
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


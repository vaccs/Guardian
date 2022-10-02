
#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "print_source.h"

struct stringtree* type_print_source(
	struct type* this)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	assert(this->inheritance->print_source);
	
	struct stringtree* tree = (this->inheritance->print_source)(this);
	
	EXIT;
	return tree;
}


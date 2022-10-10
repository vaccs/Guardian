
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print_source.h"

struct stringtree* expression_print_source(
	struct expression* this,
	struct out_shared* shared)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print_source);
	
	struct stringtree* tree = (this->inheritance->print_source)(this, shared);
	
	EXIT;
	return tree;
}



#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "print_source.h"

struct stringtree* statement_print_source(
	struct statement* this,
	struct out_shared* shared,
	struct type* environment_type)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->print_source);
	
	struct stringtree* tree = (this->inheritance->print_source)(
		this, shared, environment_type);
	
	EXIT;
	return tree;
}


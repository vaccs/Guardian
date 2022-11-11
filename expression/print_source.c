
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print_source.h"

struct stringtree* expression_print_source(
	struct expression* this,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print_source);
	
	struct stringtree* tree = (this->inheritance->print_source)(this, shared, environment);
	
	EXIT;
	return tree;
}


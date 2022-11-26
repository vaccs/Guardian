
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "print_source.h"

unsigned value_print_source(
	struct stringtree* tree,
	struct value* this,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	
	assert(this->inheritance->print_source);
	
	unsigned value_id = (this->inheritance->print_source)(tree, this, shared, vtoi);
	
	EXIT;
	return value_id;
}


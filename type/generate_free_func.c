
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "generate_free_func.h"

struct stringtree* type_generate_free_func(
	struct type* this,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->generate_free_func);
	
	struct stringtree* tree = (this->inheritance->generate_free_func)(this, func_id, flookup);
	
	EXIT;
	return tree;
}


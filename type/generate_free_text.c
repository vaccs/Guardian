
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "generate_free_text.h"

struct stringtree* type_generate_free_text(
	struct type* this,
	unsigned func_id,
	struct function_lookup* flookup)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->generate_free_text);
	
	struct stringtree* tree = (this->inheritance->generate_free_text)(this, func_id, flookup);
	
	EXIT;
	return tree;
}


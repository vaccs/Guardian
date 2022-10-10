
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "generate_compare_text.h"

struct stringtree* type_generate_compare_text(
	struct type* this,
	unsigned func_id,
	struct function_lookup* flookup)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->generate_compare_text);
	
	struct stringtree* text = (this->inheritance->generate_compare_text)(this, func_id, flookup);
	
	EXIT;
	return text;
}



#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "generate_new_forward.h"

struct stringtree* type_generate_new_forward(
	struct type* this,
	unsigned func_id)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->generate_new_forward);
	
	struct stringtree* text = (this->inheritance->generate_new_forward)(this, func_id);
	
	EXIT;
	return text;
}


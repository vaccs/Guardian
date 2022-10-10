
#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "generate_new_func.h"

struct stringtree* type_generate_new_func(
	struct type* this,
	unsigned func_id,
	struct function_queue* fqueue)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->generate_new_func);
	
	struct stringtree* text = (this->inheritance->generate_new_func)(this, func_id, fqueue);
	
	EXIT;
	return text;
}


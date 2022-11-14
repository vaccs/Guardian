
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "generate_print_func.h"

struct stringtree* type_generate_print_func(
	struct type* this,
	unsigned func_id,
	struct function_queue* fqueue)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	
	dpv(this->kind);
	
	assert(this->inheritance->generate_print_func);
	
	struct stringtree* text = (this->inheritance->generate_print_func)(this, func_id, fqueue);
	
	EXIT;
	return text;
}


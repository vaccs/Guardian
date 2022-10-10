
#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "generate_typedef.h"

struct stringtree* type_generate_typedef(
	struct type* this,
	struct type_queue* tlookup)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	assert(this->inheritance->generate_typedef);
	
	struct stringtree* tree = (this->inheritance->generate_typedef)(this, tlookup);
	
	EXIT;
	return tree;
}


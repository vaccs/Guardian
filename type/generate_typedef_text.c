
#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "generate_typedef_text.h"

struct stringtree* type_generate_typedef_text(
	struct type* this,
	struct type_lookup* tlookup)
{
	ENTER;
	
	assert(this);
	
	dpv(this->kind);
	
	assert(this->inheritance);
	assert(this->inheritance->generate_typedef_text);
	
	struct stringtree* tree = (this->inheritance->generate_typedef_text)(this, tlookup);
	
	EXIT;
	return tree;
}


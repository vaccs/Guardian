
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "evaluate.h"

struct value* expression_evaluate(
	struct type_cache* tcache,
	struct expression* this,
	struct value* environment)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	assert(this->inheritance->evaluate);
	
	struct value* result = (this->inheritance->evaluate)(tcache, this, environment);
	
	EXIT;
	return result;
}


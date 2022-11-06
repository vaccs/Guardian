
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "evaluate.h"

struct value* expression_evaluate(
	struct expression* this,
	struct scope* scope)
{
	ENTER;
	
	assert(this);
	assert(this->inheritance);
	assert(this->inheritance->evaluate);
	
	struct value* result = (this->inheritance->evaluate)(this, scope);
	
	EXIT;
	return result;
}


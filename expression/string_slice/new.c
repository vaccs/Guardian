
#include <assert.h>

#include <debug.h>

#include <expression/inc.h>

/*#include <type/list/struct.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_string_slice_expression(
	struct type* type,
	struct expression* string,
	struct expression* startindex,
	struct expression* endindex)
{
	ENTER;
	
	assert(startindex || endindex);
	
	struct string_slice_expression* this = (void*) new_expression(
		ek_string_slice,
		&string_slice_expression_inheritance,
		type,
		sizeof(*this));
	
	this->string = inc_expression(string);
	
	this->startindex = inc_expression(startindex);
	
	this->endindex = inc_expression(endindex);
	
	EXIT;
	return (void*) this;
}


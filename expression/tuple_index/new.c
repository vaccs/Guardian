
#include <assert.h>

#include <debug.h>

#include <expression/inc.h>

/*#include <type/list/struct.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_tuple_index_expression(
	struct type* type,
	struct expression* tuple,
	unsigned index)
{
	ENTER;
	
	struct tuple_index_expression* this = (void*) new_expression(
		ek_tuple_index,
		&tuple_index_expression_inheritance,
		type,
		sizeof(*this));
	
	this->tuple = inc_expression(tuple);
	
	this->index = index;
	
	EXIT;
	return (void*) this;
}


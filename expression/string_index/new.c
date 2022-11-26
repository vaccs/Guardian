
#include <assert.h>

#include <debug.h>

#include <expression/inc.h>

/*#include <type/list/struct.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_string_index_expression(
	struct type* type,
	struct expression* string,
	struct expression* index)
{
	ENTER;
	
	struct string_index_expression* this = (void*) new_expression(
		ek_string_index,
		&string_index_expression_inheritance,
		type,
		sizeof(*this));
	
	this->string = inc_expression(string);
	
	this->index = inc_expression(index);
	
	EXIT;
	return (void*) this;
}


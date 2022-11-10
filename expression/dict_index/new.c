
#include <assert.h>

#include <debug.h>

#include <expression/inc.h>

/*#include <type/list/struct.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_dict_index_expression(
	struct type* type,
	struct expression* list,
	struct expression* index)
{
	ENTER;
	
	TODO;
	#if 0
	struct dict_index_expression* this = (void*) new_expression(
		ek_dict_index,
		&dict_index_expression_inheritance,
		type,
		sizeof(*this));
	
	this->list = inc_expression(list);
	
	this->index = inc_expression(index);
	
	EXIT;
	return (void*) this;
	#endif
}


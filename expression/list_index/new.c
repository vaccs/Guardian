
#include <debug.h>

#include <expression/inc.h>

#include <type/list/struct.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_list_index_expression(
	struct expression* list,
	struct expression* index)
{
	ENTER;
	
	struct type* gltype = list->type;
	assert(gltype->kind == tk_list);
	struct list_type* ltype = (void*) gltype;
	
	struct list_index_expression* this = (void*) new_expression(
		ek_list_index,
		&list_index_expression_inheritance,
		ltype->element_type,
		sizeof(*this));
	
	this->list = inc_expression(list);
	
	this->index = inc_expression(index);
	
	EXIT;
	return (void*) this;
}


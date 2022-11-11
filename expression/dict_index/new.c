
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
	struct expression* dict,
	struct expression* index)
{
	ENTER;
	
	struct dict_index_expression* this = (void*) new_expression(
		ek_dict_index,
		&dict_index_expression_inheritance,
		type,
		sizeof(*this));
	
	this->dict = inc_expression(dict);
	
	this->index = inc_expression(index);
	
	EXIT;
	return (void*) this;
}


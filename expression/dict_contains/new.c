
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_dict_contains_expression(
	struct type* type,
	struct expression* key,
	struct expression* dict)
{
	ENTER;
	
	struct dict_contains_expression* this = (void*) new_expression(
		ek_dict_contains,
		&dict_contains_expression_inheritance,
		type,
		sizeof(*this));
	
	this->key = inc_expression(key);
	
	this->dict = inc_expression(dict);
	
	EXIT;
	return (void*) this;
}


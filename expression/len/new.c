
#include <debug.h>

#include <expression/inc.h>

#include <type_cache/get_type/int.h>

#include <type/free.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_len_expression(
	struct type_cache* tcache,
	struct expression* list)
{
	ENTER;
	
	struct type* type = type_cache_get_int_type(tcache);
	
	struct len_expression* this = (void*) new_expression(
		ek_len,
		&len_expression_inheritance,
		type,
		sizeof(*this));
	
	this->list = inc_expression(list);
	
	EXIT;
	return (void*) this;
}


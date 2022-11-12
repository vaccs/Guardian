
#include <debug.h>

#include <list/value/new.h>
#include <list/value/extend.h>
#include <list/value/free.h>

#include <value/tuple/struct.h>
#include <value/tuple/new.h>

#include "run.h"

struct value* tuple_concat_run(
	struct type* type,
	struct tuple_value* left,
	struct tuple_value* right)
{
	ENTER;
	
	struct value_list* subvalues = new_value_list();
	
	value_list_extend(subvalues, left->subvalues);
	value_list_extend(subvalues, right->subvalues);
	
	struct value* value = new_tuple_value(type, subvalues);
	
	free_value_list(subvalues);
	
	EXIT;
	return value;
}



#include <debug.h>

#include <list/value/new.h>
#include <list/value/extend.h>
#include <list/value/free.h>

#include <value/list/struct.h>
#include <value/list/new.h>

#include "run.h"

struct value* list_concat_run(
	struct type* type,
	struct list_value* left,
	struct list_value* right)
{
	ENTER;
	
	struct value_list* concat = new_value_list();
	
	value_list_extend(concat,  left->elements);
	value_list_extend(concat, right->elements);
	
	struct value* value = new_list_value(type, concat);
	
	EXIT;
	return value;
}



#include <debug.h>

#include <avl/alloc_tree.h>

#include <pair/value/compare.h>
#include <pair/value/free.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_dict_value(
	struct type* type)
{
	ENTER;
	
	struct dict_value* this = (void*) new_value(
		type,
		vk_dict,
		&dict_value_inheritance,
		sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_value_pairs, free_value_pair);
	
	EXIT;
	return (void*) this;
}


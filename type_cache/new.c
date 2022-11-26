
#include <debug.h>

#include <avl/alloc_tree.h>

#include <memory/smalloc.h>

#include <type/compare.h>
#include <type/free.h>

#include "struct.h"
#include "new.h"

struct type_cache* new_type_cache()
{
	ENTER;
	
	struct type_cache* this = smalloc(sizeof(*this));
	
	this->tree = avl_alloc_tree(compare_types, NULL);
	
	this->int_type = NULL;
	
	this->bool_type = NULL;
	
	this->float_type = NULL;
	
	this->string_type = NULL;
	
	this->next = 0;
	
	EXIT;
	return this;
}


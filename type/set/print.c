
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* set_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_set);
	
	struct set_type* this = (void*) super;
	
	struct stringtree* tree = type_print2(this->element_type);
	
	stringtree_append_printf(tree, "{}");
	
	EXIT;
	return tree;
}


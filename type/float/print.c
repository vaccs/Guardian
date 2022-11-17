
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "print.h"

struct stringtree* float_type_print(
	struct type* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "float");
	
	EXIT;
	return tree;
}



#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print.h"

struct stringtree* bool_value_print(
	struct value* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct bool_value* this = (void*) super;
	
	stringtree_append_printf(tree, "%s", this->value ? "true" : "false");
	
	EXIT;
	return tree;
}


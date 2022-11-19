
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include "struct.h"
#include "print.h"

struct stringtree* float_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_float);
	
	struct stringtree* tree = new_stringtree();
	
	struct float_value* spef = (void*) super;
	
	stringtree_append_printf(tree, "%Lg", spef->value);
	
	EXIT;
	return tree;
}


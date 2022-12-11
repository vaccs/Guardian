
#include <assert.h>
#include <stdio.h>
#include <quadmath.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_strndup.h>
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
	
	char buffer[256];
	
	int len = quadmath_snprintf(buffer, sizeof(buffer), "%Qg", spef->value);
	
	assert(len < sizeof(buffer));
	
	stringtree_append_strndup(tree, buffer, len);
	
	EXIT;
	return tree;
}


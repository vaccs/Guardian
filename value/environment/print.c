
#include <assert.h>
#include <stdio.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/
/*#include <stringtree/free.h>*/

#include "struct.h"
#include "print.h"

struct stringtree* environment_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == vk_environment);
	
	struct stringtree* tree = new_stringtree();
	
	struct environment_value* spef = (void*) super;
	
	stringtree_append_printf(tree, "%Lg", spef->value);
	
	EXIT;
	return tree;
	#endif
}



#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* list_type_print_source(
	struct type* super,
	struct type_lookup* tlookup)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "struct list*");
	
	EXIT;
	return tree;
	#endif
}


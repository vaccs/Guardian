
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* int_type_print_source(
	struct type* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "int");
	
	EXIT;
	return tree;
}


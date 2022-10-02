
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_expression_print_source(
	struct expression* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "<list>\n");
	
	EXIT;
	return tree;
}















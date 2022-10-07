
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>

#include <expression/print_source.h>

#include "struct.h"
#include "print_source.h"

const char* lookup[] = {
	[ak_debug] = "debug",
	[ak_note] = "note",
	[ak_warning] = "warning",
	[ak_error] = "error",
};

struct stringtree* assertion_print_source(
	struct assertion* this,
	struct shared* shared)
{
	ENTER;
	
	struct stringtree* text = expression_print_source(this->expression, shared);
	
	TODO;
	#if 0
	struct stringtree* stringtree = new_stringtree();
	
	stringtree_append_printf(stringtree, "if (!(");
	
	stringtree_append_tree(stringtree, expression_print_source(this->expression, shared));
	
	stringtree_append_printf(stringtree, ")) {");
	
	stringtree_append_printf(stringtree, "print(\"a %%%s directive failed!\");\n", lookup[this->kind]);
	
	stringtree_append_printf(stringtree, "}");
	
	EXIT;
	return stringtree;
	#endif
}



















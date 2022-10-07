
#include <debug.h>

#include <type/struct.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/append_printf.h>*/

#include <value/print_source.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* literal_expression_print_source(
	struct expression* super,
	struct shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct literal_expression* this = (void*) super;
	
	struct stringtree* tree = value_print_source(this->value, shared);
	
	EXIT;
	return tree;
	#endif
}















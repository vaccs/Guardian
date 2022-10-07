
#include <debug.h>

/*#include <type/struct.h>*/

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

/*#include <value/print_source.h>*/

/*#include "../print_source.h"*/

#include "struct.h"
#include "print_source.h"

struct stringtree* variable_expression_print_source(
	struct expression* super,
	struct shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	struct variable_expression* this = (void*) super;
	
	struct type* type = super->type;
	
	unsigned tid = out_get_type_id(shared, type);
	
	stringtree_append_printf(tree,
		"inc_type_%u(%.*s)",
		tid, (int) this->name->len, this->name->chars);
	
	EXIT;
	return tree;
	#endif
}















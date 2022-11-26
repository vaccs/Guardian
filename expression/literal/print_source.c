
#include <debug.h>

/*#include <type/struct.h>*/

#include <value/print_source.h>

#include <misc/value_to_id/new.h>
#include <misc/value_to_id/foreach.h>
#include <misc/value_to_id/free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <value/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* literal_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	struct literal_expression* this = (void*) super;
	
	struct value_to_id* vtoi = new_value_to_id();
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	unsigned value_id = value_print_source(tree, this->value, shared, vtoi);
	
	value_to_id_foreach(vtoi, ({
		void runme(unsigned id, struct value* value)
		{
			if (value != this->value)
			{
				unsigned free_id = function_queue_submit_free(shared->fqueue, value->type);
				
				stringtree_append_printf(tree, "func_%u(value_%u);\n", free_id, id);
			}
		}
		runme;
	}));
	
	stringtree_append_printf(tree, "value_%u;", value_id);
	
	stringtree_append_printf(tree, "})");
	
	free_value_to_id(vtoi);
	
	EXIT;
	return tree;
}















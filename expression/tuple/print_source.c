
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <list/expression/foreach.h>

/*#include <parameter/struct.h>*/

/*#include <list/parameter/struct.h>*/

/*#include <type_check/unresolved/foreach.h>*/

#include <type/struct.h>

#include <expression/print_source.h>

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "struct.h"
#include "print_source.h"

struct stringtree* tuple_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_tuple);
	
	struct tuple_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"({"
	"");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = func_%u();"
	"", super->type->id, new_id);
	
	unsigned arg_counter = 0;
	
	expression_list_foreach(this->subexpressions, ({
		void runme(struct expression* subexpression)
		{
			type_queue_submit(shared->tqueue, subexpression->type);
			
			struct stringtree* subtree = expression_print_source(subexpression, shared, environment);
			
			stringtree_append_printf(tree, ""
				"result->$%u = "
			"", arg_counter++);
			
			stringtree_append_tree(tree, subtree);
			
			stringtree_append_printf(tree, ""
				";"
			"");
			
			free_stringtree(subtree);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
			"result;"
		"})"
	"");
	
	EXIT;
	return tree;
}




















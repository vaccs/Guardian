
#include <assert.h>

#include <debug.h>

/*#include <type/list/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_queue/submit_index.h>*/
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* tuple_index_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_tuple_index);
	
	struct stringtree* tree = new_stringtree();
	
	struct tuple_index_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	struct type* subtype = this->tuple->type;
	
	struct stringtree* tuple_tree = expression_print_source(this->tuple, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* tuple = ", subtype->id);
	stringtree_append_tree(tree, tuple_tree);
	stringtree_append_printf(tree, ";");
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* element = func_%u(tuple->$%u);"
	"", super->type->id, inc_id, this->index);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, subtype);
	
	stringtree_append_printf(tree, ""
		"func_%u(tuple);"
	"", free_id);
	
	stringtree_append_printf(tree, "element;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(tuple_tree);
	
	EXIT;
	return tree;
}













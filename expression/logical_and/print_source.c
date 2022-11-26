
#include <assert.h>

#include <debug.h>

/*#include <type/struct.h>*/

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

/*#include <set/string/add.h>*/

/*#include <quack/append.h>*/

#include <type_cache/get_bool_type.h>

#include <out/shared.h>
/*#include <out/function_lookup/lookup_inc.h>*/
/*#include <out/declare_queue/submit.h>*/
/*#include <out/set_queue/submit.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* logical_and_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_logical_and);
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	struct logical_and_expression* this = (void*) super;
	
	struct type* btype = type_cache_get_bool_type(shared->tcache);
	
	type_queue_submit(shared->tqueue, btype);
	
	stringtree_append_printf(tree, ""
		"({"
	"");
	
	struct stringtree* left_text = expression_print_source(this->left, shared, environment);
	
	stringtree_append_printf(tree, ""
			"struct type_%u* result = "
	"", btype->id);
	stringtree_append_tree(tree, left_text);
	stringtree_append_printf(tree, ";");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, btype);
	
	stringtree_append_printf(tree, ""
			"if (result->value)"
			"{"
				"func_%u(result);"
				"result = "
	"", free_id);
	
	struct stringtree* right_text = expression_print_source(this->right, shared, environment);
	
	stringtree_append_tree(tree, right_text);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, ""
			"}"
			"result;"
		"})"
	"");
	
	free_stringtree(left_text), free_stringtree(right_text);
	
	EXIT;
	return tree;
}




































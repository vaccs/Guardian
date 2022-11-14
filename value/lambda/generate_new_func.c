
#include <assert.h>
#include <stddef.h>
#include <debug.h>

#include <string/struct.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <scope/foreach.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/subtype_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>
#include <out/function_queue/submit_lambda_new.h>
#include <out/function_queue/submit_lambda_evaluate.h>
#include <out/function_queue/submit_lambda_free.h>

#include <value/print_source.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* lambda_value_generate_new_func(
	struct lambda_value* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, this->super.type);
	
	subtype_queue_submit_value(shared->stqueue, this);
	
	unsigned type_id = this->super.type->id;
	
	unsigned subtype_id = this->id;
	
	stringtree_append_printf(tree, "struct type_%u* func_%u()", type_id, func_id);
	
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree, "struct subtype_%u* this = malloc(sizeof(*this));", subtype_id);

	unsigned evaluate_id = function_queue_submit_lambda_value_evaluate(shared->fqueue, this);
	unsigned free_id = function_queue_submit_lambda_value_free(shared->fqueue, this);
	stringtree_append_printf(tree, "this->super.evaluate = func_%u;", evaluate_id);
	stringtree_append_printf(tree, "this->super.free = func_%u;", free_id);
	stringtree_append_printf(tree, "this->super.refcount = 1;");
	
	stringtree_append_printf(tree, "return &this->super;");
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}



































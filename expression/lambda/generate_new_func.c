

#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>
#include <type/environment/struct.h>

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_lambda_evaluate.h>
#include <out/function_queue/submit_lambda_free.h>

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* lambda_expression_generate_new_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	subtype_queue_submit_expression(shared->stqueue, this);
	
	unsigned type_id = this->super.type->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u(struct type_%u* prev)"
	"", type_id, func_id, this->environment->prev->super.id);
	
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree, "struct subtype_%u* this = malloc(sizeof(*this));", this->id);
	
	unsigned evaluate_id = function_queue_submit_lambda_expression_evaluate(shared->fqueue, this);
	stringtree_append_printf(tree, "this->super.evaluate = func_%u;", evaluate_id);
	
	unsigned free_id = function_queue_submit_lambda_expression_free(shared->fqueue, this);
	stringtree_append_printf(tree, "this->super.free = func_%u;", free_id);
	
	stringtree_append_printf(tree, "this->super.refcount = 1;");
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, (struct type*) this->environment->prev);
	stringtree_append_printf(tree, "this->prev = func_%u(prev);", inc_id);
	
	stringtree_append_printf(tree, "return &this->super;");
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}













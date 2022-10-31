
#include <debug.h>

#include <type/struct.h>

/*#include <out/function_queue/submit_lambda_new.h>*/
#include <out/function_queue/submit_lambda_evaluate.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* lambda_value_generate_new_func(
	struct lambda_value* this,
	unsigned func_id,
	struct function_queue* fqueue)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned type_id = this->super.type->id;
	
	unsigned evaluate_id = function_queue_submit_lambda_value_evaluate(fqueue, this);
	
	stringtree_append_printf(tree, ""
		"type_%u* func_%u()"
		"{"
			"type_%u* new = malloc(sizeof(*new));"
			"new->evaluate = func_%u;"
			"new->free = NULL;"
			"new->refcount = 1;"
			"new;"
		"}"
	"", type_id, func_id, type_id, evaluate_id);
	
	EXIT;
	return tree;
}





























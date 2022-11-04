
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
/*#include <out/function_queue/submit_lambda_new.h>*/
#include <out/function_queue/submit_lambda_evaluate.h>

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
	
	unsigned type_id = this->super.type->id;
	
	unsigned evaluate_id = function_queue_submit_lambda_value_evaluate(shared->fqueue, this);
	
	stringtree_append_printf(tree, ""
		"static struct type_%u* func_%u()"
		"{"
			"struct type_%u* this = malloc(sizeof(*this));"
			"this->evaluate = func_%u;"
			"this->free = NULL;"
			"this->refcount = 1;"
			"return this;"
		"}"
	"", type_id, func_id, type_id, evaluate_id);
	
	EXIT;
	return tree;
}





























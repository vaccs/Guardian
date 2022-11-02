
#include <debug.h>

#include <type/struct.h>

#include <type_check/unresolved/foreach.h>

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_lambda_evaluate.h>
#include <out/function_queue/submit_lambda_free.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* lambda_expression_generate_new_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	subtype_queue_submit(shared->stqueue, this);
	
	unsigned lambda_id = this->id;
	
	stringtree_append_printf(tree, ""
		"struct subtype_%u* func_%u("
	"", lambda_id, func_id);
	
	unresolved_foreach3(this->captured, ({
		void runme(struct string* name, struct type* type)
		{
			dpvs(name);
			
			type_queue_submit(shared->tqueue, type);
			
			stringtree_append_printf(tree, ""
				"struct type_%u* $%.*s, "
			"", type->id, name->len, name->chars);
		}
		runme;
	}));
	
	unsigned evaluate_id = function_queue_submit_lambda_expression_evaluate(shared->fqueue, this);
	
	unsigned free_id = function_queue_submit_lambda_expression_free(shared->fqueue, this);
	
	stringtree_append_printf(tree, ""
			"void)"
		"{"
			"subtype_%u* this = malloc(sizeof(*new));"
			"this->super.evaluate = func_%u;"
			"this->super.free = func_%u;"
			"this->super.refcount = 1;"
	"", lambda_id, evaluate_id, free_id);
	
	unresolved_foreach3(this->captured, ({
		void runme(struct string* name, struct type* type)
		{
			dpvs(name);
			
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, type);
			
			dpv(inc_id);
			
			stringtree_append_printf(tree, ""
				"this->$%.*s = func_%u($%.*s);"
			"", name->len, name->chars, inc_id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
			"return this;"
		"}"
	"");
	
	EXIT;
	return tree;
}













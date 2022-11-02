
#include <debug.h>

#include <type/struct.h>

#include <list/parameter/foreach.h>

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
#include <out/type_queue/submit.h>

#include <expression/print_source.h>

#include <type_check/unresolved/foreach.h>

/*#include <out/function_queue/submit_lambda_evaluate.h>*/
/*#include <out/function_queue/submit_lambda_free.h>*/

#include "struct.h"
#include "generate_evaluate_func.h"

struct stringtree* lambda_expression_generate_evaluate_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	subtype_queue_submit(shared->stqueue, this);
	
	unsigned type_id = this->super.type->id, lambda_id = this->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u(struct type_%u* super"
	"", type_id, func_id, type_id);
	
	parameter_list_foreach(this->parameters, ({
		void runme(struct string* name, struct type* type)
		{
			stringtree_append_printf(tree, ""
				", struct type_%u* $%.*s"
			"", type->id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
			")"
		"{"
			"struct subtype_%u* this = (void*) super;"
			"return "
	"", lambda_id);
	
	struct stringtree* subtree = expression_print_source(this->body, shared);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ""
			";"
		"}"
	"");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}



























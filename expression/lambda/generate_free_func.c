
#include <debug.h>

#include <type/struct.h>

#include <type_check/unresolved/foreach.h>

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
#include <out/function_queue/submit_free.h>
/*#include <out/function_queue/submit_lambda_free.h>*/

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* lambda_expression_generate_free_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	subtype_queue_submit(shared->stqueue, this);
	
	unsigned type_id = this->super.type->id;
	
	unsigned lambda_id = this->id;
	
	stringtree_append_printf(tree, ""
		"void func_%u(struct type_%u* super)"
		"{"
			"struct subtype_%u* this = super;"
	"", func_id, type_id, lambda_id);
	
	unresolved_foreach3(this->captured, ({
		void runme(struct string* name, struct type* type)
		{
			dpvs(name);
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, type);
			
			stringtree_append_printf(tree, ""
				"func_%u(this->$%.*s);"
			"", free_id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
		"}"
	"");
	
	EXIT;
	return tree;
}













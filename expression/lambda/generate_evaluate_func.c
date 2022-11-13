
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <string/struct.h>

#include <type/struct.h>
#include <type/lambda/struct.h>
#include <type/environment/struct.h>

#include <list/parameter/foreach.h>

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
#include <out/type_queue/submit.h>

#include <expression/print_source.h>

#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>
#include <out/function_queue/submit_lambda_evaluate.h>
#include <out/function_queue/submit_lambda_free.h>

#include "struct.h"
#include "generate_evaluate_func.h"

struct stringtree* lambda_expression_generate_evaluate_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct lambda_type* ltype = (void*) this->super.type;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u(struct type_%u* super"
	"", ltype->rettype->id, func_id, this->super.type->id);
	
	parameter_list_foreach(this->parameters, ({
		void runme(struct string* name, struct type* type)
		{
			stringtree_append_printf(tree, ""
				", struct type_%u* $%.*s"
			"", type->id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ")");
	
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree,
		"struct subtype_%u* this = (void*) super;",
		this->id);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, (struct type*) this->environment);
	
	stringtree_append_printf(tree,
		"struct type_%u* environment = func_%u(this->prev);",
		this->environment->super.id, new_id);
	
	parameter_list_foreach(this->parameters, ({
		void runme(struct string* name, struct type* type)
		{
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, type);
			
			stringtree_append_printf(tree, ""
				"environment->$%.*s = func_%u($%.*s);"
			"", name->len, name->chars, inc_id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, "struct type_%u* result = ", ltype->rettype->id);
	struct stringtree* subtree = expression_print_source(this->body, shared, this->environment);
	stringtree_append_tree(tree, subtree);
	stringtree_append_printf(tree, ";");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, (struct type*) this->environment);
	stringtree_append_printf(tree, "func_%u(environment);", free_id);
	
	stringtree_append_printf(tree, "return result;");
	
	stringtree_append_printf(tree, "}");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}



























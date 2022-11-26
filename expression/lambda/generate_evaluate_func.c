
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_string.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <string/struct.h>

#include <type/struct.h>
#include <type/lambda/struct.h>
#include <type/environment/struct.h>

/*#include <list/parameter/foreach.h>*/

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
#include <out/type_queue/submit.h>

#include <expression/print_source.h>

#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>
#include <out/function_queue/submit_lambda_evaluate.h>
#include <out/function_queue/submit_lambda_free.h>

#include <list/named_type/foreach.h>

#include <named/type/struct.h>

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
	
	named_type_list_foreach(this->parameters, ({
		void runme(struct named_type* ntype)
		{
			stringtree_append_printf(tree, ", struct type_%u* $", ntype->type->id);
			
			stringtree_append_string(tree, ntype->name);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ")");
	
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree,
		"struct subtype_%u* this = (void*) super;",
		this->id);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, this->environment);
	
	stringtree_append_printf(tree,
		"struct type_%u* environment = func_%u();",
		this->environment->id, new_id);
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue,
		((struct environment_type* ) this->environment)->prev);
	
	stringtree_append_printf(tree,
		"environment->prev = func_%u(this->prev);", inc_id);
	
	named_type_list_foreach(this->parameters, ({
		void runme(struct named_type* ntype)
		{
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, ntype->type);
			
			stringtree_append_printf(tree, "environment->$");
			
			stringtree_append_string(tree, ntype->name);
			
			stringtree_append_printf(tree, " = func_%u($", inc_id);
			
			stringtree_append_string(tree, ntype->name);
			
			stringtree_append_printf(tree, ");");
		}
		runme;
	}));
	
	stringtree_append_printf(tree, "struct type_%u* result = ", ltype->rettype->id);
	struct stringtree* subtree = expression_print_source(this->body, shared, this->environment);
	stringtree_append_tree(tree, subtree);
	stringtree_append_printf(tree, ";");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, this->environment);
	stringtree_append_printf(tree, "func_%u(environment);", free_id);
	
	stringtree_append_printf(tree, "return result;");
	
	stringtree_append_printf(tree, "}");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}



























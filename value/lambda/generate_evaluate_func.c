
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <type/struct.h>
#include <type/lambda/struct.h>

/*#include <type/environment/struct.h>*/

/*#include <list/parameter/foreach.h>*/

#include <type_cache/get_environment_type.h>

/*#include <parameter/struct.h>*/

/*#include <string/struct.h>*/

/*#include <scope/foreach.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/print_source.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>

#include <list/named_type/foreach.h>

#include <stringtree/append_string.h>

#include <named/type/struct.h>
#include <named/type/inc.h>

/*#include "../print_source.h"*/

#include "struct.h"
#include "generate_evaluate_func.h"

struct stringtree* lambda_value_generate_evaluate_func(
	struct lambda_value* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, this->super.type);
	
	struct lambda_type* ltype = (void*) this->super.type;
	
	type_queue_submit(shared->tqueue, ltype->rettype);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u(struct type_%u* super"
	"", ltype->rettype->id, func_id, this->super.type->id);
	
	named_type_list_foreach(this->parameters, ({
		void runme(struct named_type* ntype)
		{
			type_queue_submit(shared->tqueue, ntype->type);
			
			stringtree_append_printf(tree, ", struct type_%u* $", ntype->type->id);
			
			stringtree_append_string(tree, ntype->name);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ")");
	
	stringtree_append_printf(tree, "{");
	
	struct avl_tree_t* environment_tree = avl_alloc_tree(compare_named_types, free_named_type);
	
	named_type_list_foreach(this->parameters, ({
		void runme(struct named_type* ntype)
		{
			void* ptr222 = avl_insert(environment_tree, inc_named_type(ntype));
			assert(ptr222);
		}
		runme;
	}));
	
	struct type* environment = type_cache_get_environment_type2(
		shared->tcache, this->captured ? this->captured->type : NULL, environment_tree);
	
	type_queue_submit(shared->tqueue, environment);
	
	unsigned etid = environment->id;
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, environment);
	
	stringtree_append_printf(tree, "struct type_%u* environment = func_%u();", etid, new_id);
	
	if (this->captured)
	{
		stringtree_append_printf(tree, "struct subtype_%u* this = (void*) super;", this->id);
		
		unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->captured->type);
		
		stringtree_append_printf(tree, "environment->prev = func_%u(this->captured);", inc_id);
	}
	
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
	struct stringtree* subtree = expression_print_source(this->body, shared, environment);
	stringtree_append_tree(tree, subtree);
	stringtree_append_printf(tree, ";");
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, environment);
	stringtree_append_printf(tree, "func_%u(environment);", free_id);
	
	stringtree_append_printf(tree, "return result;");
	
	stringtree_append_printf(tree, "}");
	
	avl_free_tree(environment_tree);
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}

















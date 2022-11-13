
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

#include <type_cache/get_type/environment.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/subtype_queue/submit.h>
#include <out/function_queue/submit_new.h>
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
	
	unsigned evaluate_id = function_queue_submit_lambda_value_evaluate(shared->fqueue, this);
	
	unsigned free_id = function_queue_submit_lambda_value_free(shared->fqueue, this);
	
	stringtree_append_printf(tree, "struct type_%u* func_%u()", type_id, func_id);
	stringtree_append_printf(tree, "{");
	
	stringtree_append_printf(tree, "struct subtype_%u* this = malloc(sizeof(*this));", subtype_id);

	stringtree_append_printf(tree, "this->super.evaluate = func_%u;", evaluate_id);
	stringtree_append_printf(tree, "this->super.free = func_%u;", free_id);
	stringtree_append_printf(tree, "this->super.refcount = 1;");
	
	unsigned counter = 0;
	
	struct environment_type* prev = NULL;
	
	scope_foreach_layer(this->captured, ({
		void runme(struct scope* layer)
		{
			counter++;
			
			struct avl_tree_t* environment_tree = avl_alloc_tree(compare_named_types, free_named_type);
			
			scope_foreach(layer, ({
				void runme(struct string* name, struct value* value)
				{
					struct named_type* ntype = new_named_type(name, value->type);
					
					void* ptr222 = avl_insert(environment_tree, ntype);
					
					assert(ptr222);
				}
				runme;
			}));
			
			struct environment_type* environment = type_cache_get_environment_type2(shared->tcache, prev, environment_tree);
			
			type_queue_submit(shared->tqueue, (struct type*) environment);
			
			unsigned etid = ((struct type*) environment)->id;
			
			unsigned new_id = function_queue_submit_new(shared->fqueue,(struct type*) environment);
			
			if (prev)
				stringtree_append_printf(tree, "struct type_%u* env_%u = func_%u(env_%u);", etid, counter, new_id, counter - 1);
			else
				stringtree_append_printf(tree, "struct type_%u* env_%u = func_%u();", etid, counter, new_id);
			
			scope_foreach(layer, ({
				void runme(struct string* name, struct value* value)
				{
					stringtree_append_printf(tree, "env_%u->$%.*s = ", counter, name->len, name->chars);
					
					struct stringtree* subtree = value_print_source(value, shared);
					
					stringtree_append_tree(tree, subtree);
					
					stringtree_append_printf(tree, ";");
					
					free_stringtree(subtree);
				}
				runme;
			}));
			
			if (prev)
			{
				unsigned free_id = function_queue_submit_free(shared->fqueue, (struct type*) prev);
				
				stringtree_append_printf(tree, "func_%u(env_%u);", free_id, counter - 1);
			}
			
			avl_free_tree(environment_tree);
			
			prev = environment;
		}
		runme;
	}));
	
	if (prev)
	{
		stringtree_append_printf(tree, "this->captured = env_%u;", counter);
	}
	
	this->captured_type = prev;
	
	stringtree_append_printf(tree, "return &this->super;");
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}



































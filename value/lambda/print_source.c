
#include <stddef.h>
#include <assert.h>

#include <debug.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <scope/foreach.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/function_queue/struct.h>
#include <out/type_queue/submit.h>
#include <out/subtype_queue/submit.h>

#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_lambda_new.h>
#include <out/function_queue/submit_free.h>

#include <misc/value_to_id/add.h>
#include <misc/value_to_id/discard.h>

#include <scope/foreach.h>

#include <type_cache/get_type/environment.h>

/*#include <mpz/struct.h>*/

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* lambda_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_lambda);
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct lambda_value* this = (void*) super;
		
		if (!this->id) this->id = shared->fqueue->lambda_id++;
		
		type_queue_submit(shared->tqueue, this->super.type);
		
		subtype_queue_submit_value(shared->stqueue, this);
		
		unsigned new_id = function_queue_submit_lambda_value_new(shared->fqueue, this);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u();",
			super->type->id, value_id, new_id);
		
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
						
						struct stringtree* subtree = value_print_source(value, shared, vtoi);
						
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
			stringtree_append_printf(tree, "((struct subtype_%u*) value_%u)->captured = env_%u;", this->id, value_id, counter);
		}
		
		stringtree_append_printf(tree, "value_%u;", value_id);
		
		this->captured_type = prev;
		
		value_to_id_discard(vtoi, super);
	}
	else
	{
		unsigned inc_id = function_queue_submit_inc(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "func_%u(value_%u);", inc_id, value_id);
	}
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_new.h>
#include <out/type_queue/submit.h>

#include <misc/value_to_id/add.h>

#include <avl/foreach.h>

#include <named/value/struct.h>

#include <out/function_queue/submit_inc.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

unsigned environment_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_environment);
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct environment_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u();",
			super->type->id, value_id, new_id);
		
		avl_foreach(this->variables, ({
			void runme(void* ptr)
			{
				struct named_value* nvalue = ptr;
				
				unsigned subvalue_id = value_print_source(tree, nvalue->value, shared, vtoi);
				
				unsigned inc_id = function_queue_submit_inc(shared->fqueue, nvalue->value->type);
				
				stringtree_append_printf(tree, "value_%u->$%.*s = func_%u(value_%u);\n",
					value_id, nvalue->name->len, nvalue->name->chars, inc_id, subvalue_id);
			}
			runme;
		}));
		
		if (this->prev)
		{
			unsigned prev_id = value_print_source(tree, this->prev, shared, vtoi);
			
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->prev->type);
			
			stringtree_append_printf(tree, "value_%u->prev = func_%u(value_%u);\n",
				value_id, inc_id, prev_id);
		}
	}
	
	EXIT;
	return value_id;
}



























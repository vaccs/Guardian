
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>

#include <list/value/foreach.h>

/*#include <type/struct.h>*/
#include <type/list/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>

#include <misc/value_to_id/add.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

unsigned list_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_list);
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct list_value* this = (void*) super;
		
/*		struct list_type* ltype = (void*) super->type;*/
		
/*		struct type* etype = ltype->element_type;*/
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, ""
			"struct type_%u* value_%u = func_%u();"
		"", super->type->id, value_id, new_id);
		
		value_list_foreach(this->elements, ({
			void runme(struct value* value)
			{
				unsigned element_id = value_print_source(tree, value, shared, vtoi);
				
				unsigned append_id = function_queue_submit_append(shared->fqueue, super->type);
				
				stringtree_append_printf(tree, "func_%u(value_%u, value_%u);", append_id, value_id, element_id);
			}
			runme;
		}));
	}
	
	EXIT;
	return value_id;
}














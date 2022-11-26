
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_new.h>*/
#include <out/type_queue/submit.h>

#include <out/function_queue/submit_new.h>

#include <misc/value_to_id/add.h>

#include "struct.h"
#include "print_source.h"

unsigned float_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_float);
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct float_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u(%Lg);",
				super->type->id, value_id, new_id, this->value);
	}
	
	EXIT;
	return value_id;
}





























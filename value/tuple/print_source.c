
#include <assert.h>

#include <stdbool.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>

#include <list/value/foreach.h>

/*#include <out/type_queue/submit.h>*/

#include <out/type_queue/submit.h>

#include <out/function_queue/submit_free.h>
#include <out/function_queue/submit_inc.h>

#include <value/print_source.h>

#include <out/function_queue/submit_new.h>

/*#include <mpz/struct.h>*/

#include <misc/value_to_id/add.h>
/*#include <misc/value_to_id/discard.h>*/

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

unsigned tuple_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_tuple);
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct tuple_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "struct type_%u* value_%u = func_%u();", super->type->id, value_id, new_id);
		
		unsigned argcounter = 0;
		
		value_list_foreach(this->subvalues, ({
			void runme(struct value* value)
			{
				unsigned subvalue_id = value_print_source(tree, value, shared, vtoi);
				
				unsigned inc_id = function_queue_submit_inc(shared->fqueue, value->type);
				
				stringtree_append_printf(tree, "value_%u->$%u = func_%u(value_%u);",
					value_id, argcounter, inc_id, subvalue_id);
				
				argcounter++;
			}
			runme;
		}));
	}
	
	EXIT;
	return value_id;
}

















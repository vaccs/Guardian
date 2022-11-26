
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>
/*#include <stringtree/free.h>*/

/*#include <set/value/foreach.h>*/
#include <list/value/struct.h>

#include <type/struct.h>
#include <type/set/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
/*#include <out/function_queue/submit_append.h>*/
/*#include <out/function_queue/submit_free.h>*/

#include <misc/value_to_id/add.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

unsigned set_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct set_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		struct set_type* stype = (void*) super->type;
		
		unsigned n = this->elements->n;
		
		stringtree_append_printf(tree,
			"struct type_%u** elements = malloc(sizeof(*elements) * %u);", stype->element_type->id, n);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u(elements, %u);", super->type->id, value_id, new_id, n);
		
		for (unsigned i = 0; i < n; i++)
		{
			unsigned element_id = value_print_source(tree, this->elements->data[i], shared, vtoi);
			
			unsigned inc_id = function_queue_submit_inc(
				shared->fqueue, stype->element_type);
			
			stringtree_append_printf(tree,
				"elements[%u] = func_%u(value_%u);", i, inc_id, element_id);
		}
	}
	
	EXIT;
	return value_id;
}














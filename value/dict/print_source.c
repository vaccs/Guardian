
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>
/*#include <stringtree/free.h>*/

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_new.h>

#include <type/struct.h>

#include <pair/value/struct.h>

#include <list/value_pair/struct.h>

#include <misc/value_to_id/add.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

unsigned dict_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_dict);
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct dict_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned n = this->elements->n;
		
		stringtree_append_printf(tree,
			"struct type_%u_pair* data = malloc(sizeof(*data) * %u);", super->type->id, n);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u(data, %u);", super->type->id, value_id, new_id, n);
		
		for (unsigned i = 0; i < n; i++)
		{
			struct value_pair* element = this->elements->data[i];
			
			{
				unsigned key_id = value_print_source(tree, element->key, shared, vtoi);
				
				unsigned inc_id = function_queue_submit_inc(shared->fqueue, element->key->type);
				
				stringtree_append_printf(tree, "data[%u].key = func_%u(value_%u);\n", i, inc_id, key_id);
			}
			
			{
				unsigned val_id = value_print_source(tree, element->value, shared, vtoi);
				
				unsigned inc_id = function_queue_submit_inc(shared->fqueue, element->value->type);
				
				stringtree_append_printf(tree, "data[%u].value = func_%u(value_%u);\n", i, inc_id, val_id);
			}
		}
	}
	
	EXIT;
	return value_id;
}














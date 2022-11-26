
#include <stddef.h>
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

/*#include <avl/alloc_tree.h>*/
/*#include <avl/insert.h>*/
/*#include <avl/free_tree.h>*/

/*#include <named/type/new.h>*/
/*#include <named/type/compare.h>*/
/*#include <named/type/free.h>*/

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>
/*#include <stringtree/free.h>*/

#include <type/struct.h>

#include <out/shared.h>
#include <out/function_queue/struct.h>
#include <out/type_queue/submit.h>
#include <out/subtype_queue/submit.h>

/*#include <out/function_queue/submit_new.h>*/
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_lambda_new.h>
/*#include <out/function_queue/submit_free.h>*/

#include <misc/value_to_id/add.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

unsigned lambda_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_lambda);
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct lambda_value* this = (void*) super;
		
		if (!this->id) this->id = shared->fqueue->lambda_id++;
		
		type_queue_submit(shared->tqueue, super->type);
		
		subtype_queue_submit_value(shared->stqueue, this);
		
		unsigned new_id = function_queue_submit_lambda_value_new(shared->fqueue, this);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u();",
			super->type->id, value_id, new_id);
		
		if (this->captured)
		{
			unsigned captured_id = value_print_source(tree, this->captured, shared, vtoi);
			
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, this->captured->type);
			
			stringtree_append_printf(tree,
				"((struct subtype_%u*) value_%u)->captured = func_%u(value_%u);",
				this->id, value_id, inc_id, captured_id);
		}
	}
	
	EXIT;
	return value_id;
}










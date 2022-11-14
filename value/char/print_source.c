
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <type/struct.h>*/

#include <misc/value_to_id/add.h>
#include <misc/value_to_id/discard.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* char_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct char_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "func_%u(%u)", new_id, this->value);
		
		value_to_id_discard(vtoi, super);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return tree;
}





























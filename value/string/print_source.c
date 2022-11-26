
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <misc/value_to_id/add.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>

#include "struct.h"
#include "print_source.h"

unsigned string_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		assert(super->kind == vk_string);
		
		struct string_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u(memcpy(malloc(%u), \"",
			super->type->id, value_id, new_id, this->len);
		
		for (unsigned i = 0, n = this->len; i < n; i++)
			stringtree_append_printf(tree, "\\x%hhX", this->chars[i]);
		
		stringtree_append_printf(tree,
			"\", %u), %u);",
			this->len, this->len);
	}
	
	EXIT;
	return value_id;
}






























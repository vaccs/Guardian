
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>

#include <mpz/struct.h>

#include <misc/value_to_id/add.h>

#include "struct.h"
#include "print_source.h"

unsigned int_value_print_source(
	struct stringtree* tree,
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	assert(super->kind == vk_int);
	
	struct int_value* this = (void*) super;
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "struct type_%u* value_%u = func_%u();",
			super->type->id, value_id, new_id);
		
		if (mpz_fits_slong_p(this->value->mpz))
		{
			signed long val = mpz_get_si(this->value->mpz);
			
			stringtree_append_printf(tree, "mpz_set_si(value_%u->value, %li);", value_id, val);
		}
		else
		{
			TODO;
			#if 0
			stringtree_append_printf(tree, "mpz_set_str(new->mpz);");
			#endif
		}
		
	}
	
	EXIT;
	return value_id;
}
















#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_new.h>*/
#include <out/type_queue/submit.h>

#include <out/function_queue/submit_new.h>

#include <mpz/struct.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* integer_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct integer_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	unsigned tid = super->type->id;
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "struct type_%u* new = func_%u();", tid, new_id);
	
	if (mpz_fits_slong_p(this->integer->mpz))
	{
		signed long val = mpz_get_si(this->integer->mpz);
		
		stringtree_append_printf(tree, "mpz_set_si(new->value, %li);", val);
	}
	else
	{
		TODO;
		#if 0
		stringtree_append_printf(tree, "mpz_set_str(new->mpz);");
		#endif
	}
	
	stringtree_append_printf(tree, "new;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}















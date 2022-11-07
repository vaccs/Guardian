
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

/*#include <type/struct.h>*/

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_new.h>*/
#include <out/type_queue/submit.h>

#include <out/function_queue/submit_new.h>

/*#include <mpz/struct.h>*/

#include "struct.h"
#include "print_source.h"

struct stringtree* float_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct float_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(%Lg)", new_id, this->value);
	
	EXIT;
	return tree;
}






























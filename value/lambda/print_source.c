
#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/append_printf.h>*/

/*#include <type/struct.h>*/

#include <out/shared.h>
/*#include <out/type_queue/submit.h>*/

#include <out/function_queue/submit_lambda_new.h>

/*#include <mpz/struct.h>*/

#include "struct.h"
#include "print_source.h"

struct stringtree* lambda_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct lambda_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned new_id = function_queue_submit_lambda_value_new(shared->fqueue, this);
	
	stringtree_append_printf(tree, "func_%u()", new_id);
	
	EXIT;
	return tree;
}
















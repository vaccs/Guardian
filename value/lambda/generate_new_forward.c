
#include <assert.h>
#include <stddef.h>
#include <debug.h>

/*#include <string/struct.h>*/

/*#include <avl/alloc_tree.h>*/
/*#include <avl/insert.h>*/
/*#include <avl/free_tree.h>*/

/*#include <named/type/new.h>*/
/*#include <named/type/compare.h>*/
/*#include <named/type/free.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/free.h>*/

#include <type/struct.h>

/*#include <scope/foreach.h>*/

/*#include <out/shared.h>*/
/*#include <out/type_queue/submit.h>*/
/*#include <out/subtype_queue/submit.h>*/
/*#include <out/function_queue/submit_new.h>*/
/*#include <out/function_queue/submit_inc.h>*/
/*#include <out/function_queue/submit_free.h>*/
/*#include <out/function_queue/submit_lambda_new.h>*/
/*#include <out/function_queue/submit_lambda_evaluate.h>*/
/*#include <out/function_queue/submit_lambda_free.h>*/

/*#include <value/print_source.h>*/

#include "struct.h"
#include "generate_new_forward.h"

struct stringtree* lambda_value_generate_new_forward(
	struct lambda_value* this,
	unsigned func_id)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "auto struct type_%u* func_%u();", this->super.type->id, func_id);
	
	EXIT;
	return tree;
}



































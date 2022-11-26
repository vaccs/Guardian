
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>
#include <type/environment/struct.h>

#include <out/shared.h>
/*#include <out/subtype_queue/submit.h>*/
#include <out/function_queue/submit_free.h>
/*#include <out/function_queue/submit_lambda_free.h>*/

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* lambda_expression_generate_free_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"void func_%u(struct type_%u* super)"
		"{"
	"", func_id, this->super.type->id);
	
	stringtree_append_printf(tree, ""
		"struct subtype_%u* this = (void*) super;"
	"",  this->id);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue,
		((struct environment_type*) this->environment)->prev);
	
	stringtree_append_printf(tree, ""
		"func_%u(this->prev);"
	"",  free_id);
	
	stringtree_append_printf(tree, ""
		"}"
	"");
	
	EXIT;
	return tree;
}






















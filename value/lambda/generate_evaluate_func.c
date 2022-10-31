
#include <debug.h>

#include <type/struct.h>

#include <type/lambda/struct.h>

#include "struct.h"
#include "generate_evaluate_func.h"

struct stringtree* lambda_value_generate_evaluate_func(
	struct lambda_value* this,
	unsigned func_id,
	struct function_queue* fqueue)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct lambda_type* ltype = (void*) this->super.type;
	
	unsigned type_id = ltype->rettype->id;
	
	stringtree_append_printf(tree, ""
		"type_%u* func_%u( /* parameters */)"
		"{"
			"return /* expression */;"
		"}"
	"", type_id, func_id);
	
	EXIT;
	return tree;
}





























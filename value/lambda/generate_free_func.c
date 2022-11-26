
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* lambda_value_generate_free_func(
	struct lambda_value* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	unsigned type_id = this->super.type->id;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "void func_%u(struct type_%u* super)", func_id, type_id);
	stringtree_append_printf(tree, "{");
	
	if (this->captured)
	{
		stringtree_append_printf(tree, "struct subtype_%u* this = (void*) super;", this->id);
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->captured->type);
		
		stringtree_append_printf(tree, "func_%u(this->captured);", free_id);
	}
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}


















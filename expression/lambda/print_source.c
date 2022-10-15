
#include <debug.h>

#include <out/shared.h>
#include <out/function_queue/submit_lambda_new.h>

#include <parameter/struct.h>

#include <list/parameter/struct.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* lambda_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	assert(super->kind == ek_lambda);
	
	struct lambda_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned new_id = function_queue_submit_lambda_new(shared->fqueue, this);
	
	stringtree_append_printf(tree, ""
		"func_%u("
	"", new_id);
	
	for (unsigned i = 0, n = this->captured->n; i < n; i++)
	{
		struct string* name = this->captured->data[i]->name;
		
		// captured or forward or parameter?
		TODO;
		
		stringtree_append_printf(tree, ""
			"%.*s"
		"", name->len, name->chars);
		
		if (i + 1 < n)
		{
			stringtree_append_printf(tree, ""
				", "
			"");
		}
	}
	
	stringtree_append_printf(tree, ""
		")"
	"");
	
	TODO;
	
	EXIT;
	return tree;
}




















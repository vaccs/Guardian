
#include <debug.h>

#include <out/shared.h>
#include <out/function_queue/submit_lambda_new.h>

#include <parameter/struct.h>

#include <list/parameter/struct.h>

#include <type_check/unresolved/foreach.h>

#include <capture/struct.h>

#include <list/capture/foreach.h>

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
	
	unsigned new_id = function_queue_submit_lambda_expression_new(shared->fqueue, this);
	
	stringtree_append_printf(tree, ""
		"func_%u("
	"", new_id);
	
	capture_list_foreach(this->captured, ({
		void runme(struct capture* capture)
		{
			dpvs(capture->name);
			
			TODO;
			#if 0
			switch (kind)
			{
				case vek_parameter:
				case vek_declare:
					stringtree_append_printf(tree, "$%.*s", name->len, name->chars);
					break;
				
				case vek_captured:
					stringtree_append_printf(tree, "this->$%.*s", name->len, name->chars);
					break;
				
				default:
					TODO;
					break;
			}
			
			if (another)
				stringtree_append_printf(tree, ", ");
			#endif
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
		")"
	"");
	
	EXIT;
	return tree;
}





















#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <type/struct.h>

#include <capture/struct.h>

#include <list/capture/is_nonempty.h>
#include <list/capture/foreach.h>

#include <out/shared.h>
#include <out/subtype_queue/submit.h>
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
	
	subtype_queue_submit(shared->stqueue, this);
	
	unsigned type_id = this->super.type->id;
	
	unsigned lambda_id = this->id;
	
	stringtree_append_printf(tree, ""
		"void func_%u(struct type_%u* super)"
		"{"
	"", func_id, type_id);
	
	if (capture_list_is_nonempty(this->captured))
	{
		stringtree_append_printf(tree, ""
			"struct subtype_%u* this = (void*) super;"
		"", lambda_id);
		
		capture_list_foreach(this->captured, ({
			void runme(struct capture* capture)
			{
				dpvs(capture->name);
				
				unsigned free_id = function_queue_submit_free(shared->fqueue, capture->type);
				
				struct string* name = capture->name;
				
				stringtree_append_printf(tree, ""
					"func_%u(this->$%.*s);"
				"", free_id, name->len, name->chars);
			}
			
			runme;
		}));
	}
	
	stringtree_append_printf(tree, ""
		"}"
	"");
	
	EXIT;
	return tree;
}















#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/

/*#include <type/struct.h>*/

/*#include <type_check/unresolved/foreach.h>*/

/*#include <out/shared.h>*/
/*#include <out/subtype_queue/submit.h>*/
/*#include <out/type_queue/submit.h>*/
/*#include <out/function_queue/submit_inc.h>*/
/*#include <out/function_queue/submit_tuple_evaluate.h>*/
/*#include <out/function_queue/submit_tuple_free.h>*/

/*#include <capture/struct.h>*/

/*#include <list/capture/foreach.h>*/

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* tuple_expression_generate_new_func(
	struct tuple_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	subtype_queue_submit(shared->stqueue, this);
	
	unsigned type_id = this->super.type->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u("
	"", type_id, func_id);
	
	bool first = true;
	
	capture_list_foreach(this->captured, ({
		void runme(struct capture* capture)
		{
			struct type* type = capture->type;
			
			type_queue_submit(shared->tqueue, type);
			
			struct string* name = capture->name;
			
			if (first)
				first = false;
			else
				stringtree_append_printf(tree, ", ");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* $%.*s"
			"", type->id, name->len, name->chars);
		}
		runme;
	}));
	
	unsigned tuple_id = this->id;
	
	unsigned evaluate_id = function_queue_submit_tuple_expression_evaluate(shared->fqueue, this);
	
	unsigned free_id = function_queue_submit_tuple_expression_free(shared->fqueue, this);
	
	stringtree_append_printf(tree, ")"
		"{"
			"struct subtype_%u* this = malloc(sizeof(*this));"
			"this->super.evaluate = func_%u;"
			"this->super.free = func_%u;"
			"this->super.refcount = 1;"
	"", tuple_id, evaluate_id, free_id);
	
	capture_list_foreach(this->captured, ({
		void runme(struct capture* capture)
		{
			dpvs(capture->name);
			
			unsigned inc_id = function_queue_submit_inc(shared->fqueue, capture->type);
			
			dpv(inc_id);
			
			struct string* name = capture->name;
			
			stringtree_append_printf(tree, ""
				"this->$%.*s = func_%u($%.*s);"
			"", name->len, name->chars, inc_id, name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, ""
			"return (void*) this;"
		"}"
	"");
	
	EXIT;
	return tree;
	#endif
}













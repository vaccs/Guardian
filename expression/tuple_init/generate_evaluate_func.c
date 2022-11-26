
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_printf.h>*/
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/free.h>*/

/*#include <string/struct.h>*/

/*#include <type/struct.h>*/
/*#include <type/tuple_init/struct.h>*/

/*#include <list/parameter/foreach.h>*/

/*#include <out/shared.h>*/
/*#include <out/subtype_queue/submit.h>*/
/*#include <out/type_queue/submit.h>*/

/*#include <expression/print_source.h>*/

/*#include <list/capture/is_nonempty.h>*/

/*#include <out/function_queue/submit_tuple_init_evaluate.h>*/
/*#include <out/function_queue/submit_tuple_init_free.h>*/

#include "struct.h"
#include "generate_evaluate_func.h"

struct stringtree* tuple_init_expression_generate_evaluate_func(
	struct tuple_init_expression* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct stringtree* tree = new_stringtree();
	
	subtype_queue_submit(shared->stqueue, this);
	
	struct tuple_init_type* ltype = (void*) this->super.type;
	
	unsigned type_id = this->super.type->id;
	
	unsigned rettype_id = ltype->rettype->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u(struct type_%u* super"
	"", rettype_id, func_id, type_id);
	
	parameter_list_foreach(this->parameters, ({
		void runme(struct string* name, struct type* type)
		{
			stringtree_append_printf(tree, ""
				", struct type_%u* $%.*s"
			"", type->id, name->len, name->chars);
		}
		runme;
	}));
	
	unsigned tuple_init_id = this->id;
	
	stringtree_append_printf(tree, ""
			")"
		"{"
	"");
	
	if (capture_list_is_nonempty(this->captured))
	{
		stringtree_append_printf(tree, ""
				"struct subtype_%u* this = (void*) super;"
		"", tuple_init_id);
	}
	
	stringtree_append_printf(tree, ""
			"return "
	"");
	
	struct stringtree* subtree = expression_print_source(this->body, shared);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ""
			";"
		"}"
	"");
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
	#endif
}



























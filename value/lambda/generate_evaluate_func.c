
#include <assert.h>

#include <debug.h>

#include <type/struct.h>
#include <type/lambda/struct.h>

#include <list/parameter/struct.h>

#include <parameter/struct.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <scope/foreach.h>

#include <expression/print_source.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>

#include "struct.h"
#include "generate_evaluate_func.h"

struct stringtree* lambda_value_generate_evaluate_func(
	struct lambda_value* this,
	unsigned func_id,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned type_id = this->super.type->id;
	
	type_queue_submit(shared->tqueue, this->super.type);
	
	struct lambda_type* ltype = (void*) this->super.type;
	
	type_queue_submit(shared->tqueue, ltype->rettype);
	
	unsigned rettype_id = ltype->rettype->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u("
			"struct type_%u* _"
	"", rettype_id, func_id, type_id);
	
	for (unsigned i = 0, n = this->parameters->n; i < n; i++)
	{
		struct parameter* parameter = this->parameters->data[i];
		
		type_queue_submit(shared->tqueue, parameter->type);
		
		stringtree_append_printf(tree, ""
			", struct type_%u* $%.*s"
		"", parameter->type->id, parameter->name->len, parameter->name->chars);
	}
	
	stringtree_append_printf(tree, ""
		") {"
	"");
	
	if (this->captured)
	{
		TODO;
		#if 0
		// declare captured values:
		scope_foreach(this->captured, ({
			void runme(struct string* name, struct value* value)
			{
				TODO;
				#if 0
				stringtree_append_printf(tree, ""
				"");
				#endif
			}
			runme;
		}));
		
		stringtree_append_printf(tree, ""
			"type_%u* retval = /* expression */;"
		"", rettype_id);
		
		// free captured values:
		scope_foreach(this->captured, ({
			void runme(struct string* name, struct value* value)
			{
				TODO;
				#if 0
				stringtree_append_printf(tree, ""
				"");
				#endif
			}
			runme;
		}));
		
		stringtree_append_printf(tree, ""
			"return retval;"
		"");
		#endif
	}
	else
	{
		stringtree_append_printf(tree, ""
			"return "
		"");
		
		struct stringtree* subtree = expression_print_source(this->body, shared);
		
		stringtree_append_tree(tree, subtree);
		
		stringtree_append_printf(tree, ""
			";"
		"");
		
		free_stringtree(subtree);
	}
	
	stringtree_append_printf(tree, ""
		"}"
	"");
	
	EXIT;
	return tree;
}






























#include <debug.h>

#include <type/struct.h>

#include <type/lambda/struct.h>

#include <list/parameter/struct.h>

#include <parameter/struct.h>

#include <scope/foreach.h>

#include <expression/print_source.h>

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
	
	unsigned rettype_id = ltype->rettype->id;
	
	stringtree_append_printf(tree, ""
		"struct type_%u* func_%u("
	"", rettype_id, func_id);
	
	for (unsigned i = 0, n = this->parameters->n; i < n; i++)
	{
		struct parameter* parameter = this->parameters->data[i];
		
		stringtree_append_printf(tree, ""
			"struct type_%u* %.*s"
		"", parameter->type->id, parameter->name->len, parameter->name->chars);
		
		if (i + 1 < n)
		{
			stringtree_append_printf(tree, ", ");
		}
	}
	
	stringtree_append_printf(tree, ""
		") {"
	"");
	
	if (this->captured)
	{
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
	}
	else
	{
		stringtree_append_printf(tree, ""
			"return "
		"");
		
		struct stringtree* subtree = expression_print_source(this->body);
		
		stringtree_append_branch(tree, subtree);
		
		stringtree_append_printf(tree, ""
			";"
		"");
		
		free_string_tree(subtree);
	}
	
	stringtree_append_printf(tree, ""
		"}"
	"");
	
	EXIT;
	return tree;
}





























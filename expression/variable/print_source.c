
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

#include <set/string/add.h>

#include <quack/append.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
#include <out/declare_queue/submit.h>
#include <out/set_queue/submit.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_inc.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* variable_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct variable_expression* this = (void*) super;
	
	switch (this->kind)
	{
		case vek_parameter:
			TODO;
			break;
		
		case vek_declare:
			declare_queue_submit(shared->dqueue, this->name);
			break;
		
		case vek_grammar_rule:
			set_queue_submit(shared->squeue, this->name);
			break;
		
		default:
			TODO;
			break;
	}
	
	type_queue_submit(shared->tqueue, super->type);
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"func_%u(%.*s)"
	"", inc_id, this->name->len, this->name->chars);
	
	EXIT;
	return tree;
}















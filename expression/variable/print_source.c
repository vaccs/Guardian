
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

#include <set/string/add.h>

#include <quack/append.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>
#include <out/function_lookup/lookup_inc.h>

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
			if (stringset_add(shared->declares.queued, this->name))
				quack_append(shared->declares.todo, this->name);
			break;
		
		case vek_grammar_rule:
			if (stringset_add(shared->sets.queued, this->name))
				quack_append(shared->sets.todo, this->name);
			break;
	}
	
	type_lookup(shared->tlookup, super->type, NULL);
	
	unsigned inc_id = function_lookup_inc(shared->flookup, super->type, 0);
	
	stringtree_append_printf(tree, ""
		"func_%u(%.*s)"
	"", inc_id, this->name->len, this->name->chars);
	
	EXIT;
	return tree;
}















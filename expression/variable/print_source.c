
#include <assert.h>

#include <debug.h>

#include <type/struct.h>

#include <string/struct.h>

#include <stringtree/new.h>
/*#include <stringtree/append_tree.h>*/
#include <stringtree/append_printf.h>

#include <set/string/add.h>

#include <quack/append.h>

#include <type/environment/find_variable.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_inc.h>*/
/*#include <out/declare_queue/submit.h>*/
/*#include <out/set_queue/submit.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_inc.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* variable_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_variable);
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	struct variable_expression* this = (void*) super;
	
	dpvs(this->name);
	
	unsigned depth = environment_type_find_variable(environment, this->name, super->type);
	
	dpv(depth);
	
	stringtree_append_printf(tree, "({");
	
	stringtree_append_printf(tree, "struct type_%u* value = environment", super->type->id);
	while (depth--) stringtree_append_printf(tree, "->prev");
	stringtree_append_printf(tree, "->$%.*s;", this->name->len, this->name->chars);
	
	stringtree_append_printf(tree, "if (!value)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: use of variable '%.*s' before assignment!\\n\", argv0);", this->name->len, this->name->chars);
	stringtree_append_printf(tree, "	exit(1);");
	stringtree_append_printf(tree, "}");
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, super->type);
	stringtree_append_printf(tree, "func_%u(value);", inc_id);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}
































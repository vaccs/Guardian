
#include <assert.h>
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>
#include <type/list/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* int_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_int_form);
	
	struct int_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct expression* object = this->object;
	
	struct type* stype = object->type;
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"({"
			"struct type_%u* sub = "
	"", stype->id);
	
	struct stringtree* expression = expression_print_source(object, shared, environment);
	
	stringtree_append_tree(tree, expression);
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
			";"
			"struct type_%u* result = func_%u();"
	"", super->type->id, new_id);
	
	switch (stype->kind)
	{
		case tk_string:
		{
			stringtree_append_printf(tree, "char* buffer = malloc(sub->len + 1);");
			
			stringtree_append_printf(tree, "memcpy(buffer, sub->chars, sub->len);");
			
			stringtree_append_printf(tree, "buffer[sub->len] = 0;");
			
			stringtree_append_printf(tree, "if (mpz_set_str(result->value, buffer, 0))");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	assert(!\"TODO: bad int\");");
			stringtree_append_printf(tree, "	exit(1);");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "free(buffer);");
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, stype);
	
	stringtree_append_printf(tree, ""
			"func_%u(sub);"
			"result;"
		"})"
	"", free_id);
	
	free_stringtree(expression);
	
	EXIT;
	return tree;
}
















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

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* float_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_float_form);
	
	struct float_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct expression* object = this->object;
	
	struct type* stype = object->type;
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	{
		stringtree_append_printf(tree, "struct type_%u* sub = ", stype->id);
		
		struct stringtree* sub = expression_print_source(object, shared, environment);
		
		stringtree_append_tree(tree, sub);
		
		stringtree_append_printf(tree, ";");
		
		free_stringtree(sub);
	}
	
	switch (stype->kind)
	{
		case tk_int:
		{
			stringtree_append_printf(tree, "long double val = mpz_get_d(sub->value);");
			break;
		}
		
		case tk_string:
		{
			stringtree_append_printf(tree, "char* buffer = malloc(sub->len + 1);");
			stringtree_append_printf(tree, "memcpy(buffer, sub->chars, sub->len);");
			stringtree_append_printf(tree, "buffer[sub->len] = 0;");
			
			stringtree_append_printf(tree, "char* m;");
			stringtree_append_printf(tree, "errno = 0;");
			stringtree_append_printf(tree, "long double val = strtold(buffer, &m);");
			
			stringtree_append_printf(tree, "if (errno || *m)");
			stringtree_append_printf(tree, "{");
			stringtree_append_printf(tree, "	assert(!\"bad float! string!\");");
			stringtree_append_printf(tree, "}");
			
			stringtree_append_printf(tree, "free(buffer);");
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	{
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "struct type_%u* result = func_%u(val);", super->type->id, new_id);
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, stype);
		
		stringtree_append_printf(tree, "func_%u(sub);", free_id);
	}
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}















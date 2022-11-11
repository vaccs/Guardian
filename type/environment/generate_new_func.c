
#include <assert.h>

#include <debug.h>

#include <avl/foreach.h>

#include <named/type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* environment_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_environment);
	
	struct environment_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	if (this->prev)
	{
		TODO;
		#if 0
		stringtree_append_printf(text, ""
			"struct type_%u* func_%u(environment value)"
		"", type_id, func_id);
		#endif
	}
	else
	{
		stringtree_append_printf(text, ""
			"struct type_%u* func_%u()"
		"", super->id, func_id);
	}
	
	stringtree_append_printf(text, ""
		"{"
			"struct type_%u* this = malloc(sizeof(*this));"
	"", super->id);
	
	avl_foreach(this->variables, ({
		void runme(void* ptr)
		{
			struct named_type* ntype = ptr;
			
			stringtree_append_printf(text, ""
				"this->%.*s = NULL;"
			"", ntype->name->len, ntype->name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(text, ""
			"this->__refcount = 1;"
			"return this;"
		"}"
	"");
	
	EXIT;
	return text;
}












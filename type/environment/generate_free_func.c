
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <avl/foreach.h>

#include <named/type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* environment_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_environment);
	
	struct environment_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
	"", func_id, super->id);
	
	if (this->prev)
	{
		unsigned free_id = function_queue_submit_free(flookup, &this->prev->super);
		
		stringtree_append_printf(text, "func_%u(this->prev);", free_id);
	}
	
	avl_foreach(this->variables, ({
		void runme(void* ptr)
		{
			struct named_type* ntype = ptr;
			
			unsigned free_id = function_queue_submit_free(flookup, ntype->type);
			
			stringtree_append_printf(text, ""
				"func_%u(this->$%.*s);"
			"", free_id, ntype->name->len, ntype->name->chars);
		}
		runme;
	}));
	stringtree_append_printf(text, ""
				"free(this);"
			"}"
		"}"
	"");
	
	EXIT;
	return text;
}
















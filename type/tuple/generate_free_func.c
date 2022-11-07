
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/function_queue/submit_free.h>

#include <list/type/foreach.h>

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* tuple_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct tuple_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
	"", func_id, super->id);
	
	unsigned argcounter = 0;
	
	type_list_foreach(this->subtypes, ({
		void runme(struct type* subtype)
		{
			unsigned free_id = function_queue_submit_free(flookup, subtype);
			
			stringtree_append_printf(text, "func_%u(this->$%u);", free_id, argcounter++);
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

















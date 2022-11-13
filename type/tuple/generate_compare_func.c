
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/function_queue/submit_compare.h>

#include <list/type/foreach.h>

#include "struct.h"
#include "generate_compare_func.h"

struct stringtree* tuple_type_generate_compare_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct stringtree* text = new_stringtree();
	
	struct tuple_type* this = (void*) super;
	
	stringtree_append_printf(text, ""
		"int func_%u(const struct type_%u* a, const struct type_%u* b)"
		"{"
			"return 0"
	"", func_id, super->id, super->id);
	
	unsigned argcounter = 0;
	
	type_list_foreach(this->subtypes, ({
		void runme(struct type* subtype)
		{
			unsigned compare_id = function_queue_submit_compare(flookup, subtype);
			
			stringtree_append_printf(text, "?: func_%u(a->$%u, b->$%u)",
				compare_id, argcounter, argcounter);
			
			argcounter++;
		}
		runme;
	}));
	
	stringtree_append_printf(text, ";");
	
	stringtree_append_printf(text, "}");
	
	EXIT;
	return text;
}












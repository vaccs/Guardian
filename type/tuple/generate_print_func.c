
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <list/type/foreach.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/shared.h>
#include <out/function_queue/submit_print.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* tuple_type_generate_print_func(
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
			"printf(\"(\");"
	"", func_id, super->id);
	
	unsigned counter = 0;
	
	bool first = true;
	
	type_list_foreach(this->subtypes, ({
		void runme(struct type* subtype)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(text, "printf(\", \");");
			
			unsigned print_id = function_queue_submit_print(flookup, subtype);
			
			stringtree_append_printf(text, ""
				"func_%u(this->$%u);"
			"", print_id, counter);
			
			counter++;
		}
		runme;
	}));
	
	stringtree_append_printf(text, ""
			"printf(\")\");"
		"}"
	"");
	
	EXIT;
	return text;
}


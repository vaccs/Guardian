
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <list/type/foreach.h>

#include <out/function_queue/submit_inc.h>

#include "struct.h"
#include "generate_new_func.h"

struct stringtree* tuple_type_generate_new_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct stringtree* text = new_stringtree();
	
	struct tuple_type* this = (void*) super;
	
	stringtree_append_printf(text, ""
		"struct type_%u* func_%u("
	"", super->id, func_id);
	
	unsigned argcounter = 0;
	bool first = true;
	
	type_list_foreach(this->subtypes, ({
		void runme(struct type* subtype)
		{
			if (first)
				first = false;
			else
				stringtree_append_printf(text, ", ");
			
			stringtree_append_printf(text, "struct type_%u* arg%u", subtype->id, argcounter++);
		}
		runme;
	}));
	
	stringtree_append_printf(text, ""
				") {"
			"struct type_%u* this = malloc(sizeof(*this));"
	"", super->id);
	
	argcounter = 0;
	type_list_foreach(this->subtypes, ({
		void runme(struct type* subtype)
		{
			unsigned inc_id = function_queue_submit_inc(flookup, subtype);
			
			stringtree_append_printf(text, ""
				"this->$%u = func_%u(arg%u);"
			"", argcounter, inc_id, argcounter);
			
			argcounter++;
		}
		runme;
	}));
	
	stringtree_append_printf(text, ""
			"this->refcount = 1;"
			"return this;"
		"}"
	"");
	
	EXIT;
	return text;
}














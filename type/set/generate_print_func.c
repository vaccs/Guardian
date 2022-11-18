
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/shared.h>
#include <out/function_queue/submit_print.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* set_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_set);
	
	struct stringtree* text = new_stringtree();
	
	struct set_type* this = (void*) super;
	
	unsigned print_id = function_queue_submit_print(flookup, this->element_type);
	
	TODO;
	
	stringtree_append_printf(text, ""
		"void func_%u(const struct type_%u* this)"
		"{"
			"printf(\"{\");"
			
			"unsigned n = this->n;"
			
			"for (unsigned i = 0; i < n; i++)"
			"{"
				"if (i) printf(\", \");"
				"func_%u(this->data[i]);"
			"}"
			
			"if (!n)"
			"{"
				"printf(\"<\");"
				"printf(\">\");"
			"}"
			
			"printf(\"}\");"
		"}"
	"", func_id, super->id, print_id);
	
	EXIT;
	return text;
}















#include <debug.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* grammar_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static void func_%u(type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
				"free(this);"
			"}"
		"}"
	"", func_id, super->id);
	
	EXIT;
	return text;
}


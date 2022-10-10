
#include <debug.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include "struct.h"
#include "generate_free_text.h"

struct stringtree* lambda_type_generate_free_text(
	struct type* super,
	unsigned func_id,
	struct function_lookup* flookup)
{
	ENTER;
	
	assert(super->kind == tk_lambda);
	
	struct lambda_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(type_%u* this)"
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


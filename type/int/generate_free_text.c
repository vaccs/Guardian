
#include <debug.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include "struct.h"
#include "generate_free_text.h"

struct stringtree* int_type_generate_free_text(
	struct type* super,
	unsigned func_id,
	struct function_lookup* flookup)
{
	ENTER;
	
	assert(super->kind == tk_int);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
				"mpz_clear(this->value);"
				"free(this);"
			"}"
		"}"
	"", func_id, super->id);
	
	EXIT;
	return text;
}


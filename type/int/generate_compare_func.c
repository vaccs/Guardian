
#include <debug.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include "struct.h"
#include "generate_compare_func.h"

struct stringtree* int_type_generate_compare_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_int);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"static int func_%u(const type_%u* a, const type_%u* b)"
		"{"
			"return mpz_cmp(a->value, b->value);"
		"}"
	"", func_id, super->id, super->id);
	
	EXIT;
	return text;
}


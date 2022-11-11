
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include "struct.h"
#include "generate_compare_func.h"

struct stringtree* list_type_generate_compare_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_list);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"int func_%u(const struct type_%u* a, const struct type_%u* b)"
		"{"
			"assert(\"TODO: compare lists\");"
		"}"
	"", func_id, super->id, super->id);
	
	EXIT;
	return text;
}

#if 0

	int cmp = 0;
	ENTER;
	
	const struct list_value* A = (const void*) a;
	const struct list_value* B = (const void*) b;
	
	unsigned i = 0, a_n = A->elements->n, b_n = B->elements->n;
	
	while (!cmp && i < a_n && i < b_n)
	{
		struct value* ae = A->elements->data[i];
		struct value* be = B->elements->data[i];
		
		cmp = compare_values(ae, be);
		
		i++;
	}
	
	if (!cmp)
	{
		if (a_n > b_n)
			cmp = +1;
		else if (a_n < b_n)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
	#endif

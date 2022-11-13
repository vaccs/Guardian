
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <out/function_queue/submit_compare.h>

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
	
	struct list_type* this = (void*) super;
	
	unsigned compare_id = function_queue_submit_compare(flookup, this->element_type);
	
	stringtree_append_printf(text, ""
		"int func_%u(const struct type_%u* a, const struct type_%u* b)"
		"{"
			"int cmp = 0;"
			
			"unsigned i = 0, a_n = a->n, b_n = b->n;"
			
			"while (!cmp && i < a_n && i < b_n)"
				"cmp = func_%u(a->data[i], b->data[i]), i++;"
			
			"if (!cmp)"
			"{"
				"if (a_n > b_n)"
					"cmp = +1;"
				"else if (a_n < b_n)"
					"cmp = -1;"
			"}"
			
			"return cmp;"
		"}"
	"", func_id, super->id, super->id, compare_id);
	
	EXIT;
	return text;
}












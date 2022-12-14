
#include <assert.h>

#include <debug.h>

#include <out/function_queue/submit_free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* list_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_list);
	
	struct list_type* this = (void*) super;
	
	unsigned element_free_id = function_queue_submit_free(flookup, this->element_type);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
				"for (unsigned i = 0, n = this->n; i < n; i++)"
				"{"
					"func_%u(this->data[i]);"
				"}"
				
				"free(this->data);"
				"free(this);"
			"}"
		"}"
	"", func_id, super->id, element_free_id);
	
	EXIT;
	return text;
}


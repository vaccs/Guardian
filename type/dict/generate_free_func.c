
#include <assert.h>

#include <debug.h>

#include <out/function_queue/submit_free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* dict_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_dict);
	
	struct dict_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	unsigned free_key_id = function_queue_submit_free(flookup, this->key);
	unsigned free_val_id = function_queue_submit_free(flookup, this->value);
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
				"for (unsigned i = 0, n = this->n; i < n; i++)"
				"{"
					"func_%u(this->data[i].key);"
					"func_%u(this->data[i].value);"
				"}"
				
				"free(this->data);"
				"free(this);"
			"}"
		"}"
	"", func_id, super->id, free_key_id, free_val_id);
	
	EXIT;
	return text;
}




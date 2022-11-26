
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include <list/named_type/struct.h>

#include <named/type/struct.h>

#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "generate_free_func.h"

struct stringtree* grammar_type_generate_free_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct grammar_type* this = (void*) super;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(struct type_%u* this)"
		"{"
			"if (this && !--this->refcount)"
			"{"
	"", func_id, super->id);
	
	for (unsigned i = 0, n = this->fields->n; i < n; i++)
	{
		struct named_type* p = this->fields->data[i];
		
		unsigned free_id = function_queue_submit_free(flookup, p->type);
		
		stringtree_append_printf(text, ""
			"func_%u(this->$%.*s); "
		"", free_id, p->name->len, p->name->chars);
	}
	
	stringtree_append_printf(text, ""
				"free(this);"
			"}"
		"}"
	"");
	
	EXIT;
	return text;
}



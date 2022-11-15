
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* bool_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	unsigned type_id = super->id;
	
	assert(super->kind == tk_bool);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(const struct type_%u* this)"
		"{"
			"printf(\"%%s\", this->value ? \"true\" : \"false\");"
		"}"
	"", func_id, type_id);
	
	EXIT;
	return text;
}


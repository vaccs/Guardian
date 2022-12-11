
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* float_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_float);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(const struct type_%u* this)"
		"{"
			"char buffer[256] = {};"
			"int len = quadmath_snprintf(buffer, sizeof(buffer),"
				"\"%%Qg\", this->value);"
			"assert(len < sizeof(buffer));"
			"printf(\"%%s\", buffer);"
		"}"
	"", func_id, super->id);
	
	EXIT;
	return text;
}















#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>

#include <type/struct.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>
#include <out/function_lookup/lookup_free.h>

#include "struct.h"
#include "print_source.h"

const char* lookup[] = {
	[ak_debug] = "debug",
	[ak_note] = "note",
	[ak_warning] = "warning",
	[ak_error] = "error",
};

struct stringtree* assertion_print_source(
	struct assertion* this,
	struct out_shared* shared)
{
	ENTER;
	
	type_lookup(shared->tlookup, this->expression->type);
	
	struct type* type = this->expression->type;
	
	unsigned tid = type->id;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"{"
			"type_%u* assertion = "
	"", tid);
	
	stringtree_append_tree(text, expression_print_source(this->expression, shared));
	
	unsigned free_id = function_lookup_free(shared->flookup, type);
	
	stringtree_append_printf(text, ""
			";"
			"if (!assertion->value)"
			"{"
				"exit(1);"
			"}"
			"func_%u(assertion);"
		"}"
	"", free_id);
	
	EXIT;
	return text;
}



















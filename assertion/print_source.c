
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <out/shared.h>
/*#include <out/type_lookup/lookup.h>*/
/*#include <out/function_lookup/lookup_free.h>*/
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "print_source.h"

const char* lookup[] = {
	[ak_note] = "note",
	[ak_warning] = "warning",
	[ak_error] = "error",
};

struct stringtree* assertion_print_source(
	struct assertion* this,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct expression* expression = this->expression;
	
	struct type* type = expression->type;
	
	type_queue_submit(shared->tqueue, type);
	
	unsigned tid = type->id;
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"{"
			"struct type_%u* assertion = "
	"", tid);
	
	struct stringtree* subtext = expression_print_source(
		this->expression, shared, environment);
	
	stringtree_append_tree(text, subtext);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, type);
	
	stringtree_append_printf(text, ""
			";"
			
			"if (!assertion->value)"
			"{"
				"fprintf(stderr, \"%%s: %%%%%s assertion failed!\\n\", argv0);"
				"exit(1);"
			"}"
			
			"func_%u(assertion);"
		"}"
	"", lookup[this->kind], free_id);
	
	free_stringtree(subtext);
	
	EXIT;
	return text;
}




















#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/stream.h>
#include <stringtree/free.h>

/*#include <out/function_lookup/lookup_free.h>*/

#include "struct.h"
#include "generate_compare_func.h"

struct stringtree* grammar_type_generate_compare_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, "%s: cannot make comparisons on grammar datatypes!\n", argv0);
	
	stringtree_stream(text, stderr);
	
	free_stringtree(text);
	
	exit(1);
	
	EXIT;
	return text;
}












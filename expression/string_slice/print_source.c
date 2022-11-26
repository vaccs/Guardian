
#include <assert.h>

#include <debug.h>

/*#include <type/list/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <type_cache/get_int_type.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
/*#include <out/function_queue/submit_append.h>*/
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* string_slice_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_string_slice);
	
	struct string_slice_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	{
		struct stringtree* subtree = expression_print_source(this->string, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* string = ", this->string->type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
	}
	
	struct type* index_type = type_cache_get_int_type(shared->tcache);
	type_queue_submit(shared->tqueue, index_type);
	
	if (this->startindex)
	{
		struct stringtree* subtree = expression_print_source(this->startindex, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* start = ", index_type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
		
		stringtree_append_printf(tree, ""
			"unsigned native_start;"
			""
			"if (mpz_fits_uint_p(start->value) && (native_start = mpz_get_ui(start->value)) > string->len)"
			"{"
				"fprintf(stderr, \"%%s: cannot generate slice starting from "
					"index %%u in string %%u characters long!\\n\", argv0, native_start, string->len);"
				"exit(1);"
			"}"
		"");
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->startindex->type);
		stringtree_append_printf(tree, "func_%u(start);", free_id);
	}
	else
	{
		stringtree_append_printf(tree, "unsigned native_start = 0;");
	}
	
	if (this->endindex)
	{
		struct stringtree* subtree = expression_print_source(this->endindex, shared, environment);
		stringtree_append_printf(tree, "struct type_%u* end = ", index_type->id);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
		
		stringtree_append_printf(tree, ""
			"unsigned native_end;"
			""
			"if (mpz_fits_uint_p(end->value) && (native_end = mpz_get_ui(end->value)) > string->len)"
			"{"
				"fprintf(stderr, \"%%s: cannot generate slice ending "
					"on index %%u in string %%u characters long!\\n\", argv0, native_end, string->len);"
				"exit(1);"
			"}"
		"");
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->endindex->type);
		stringtree_append_printf(tree, "func_%u(end);", free_id);
	}
	else
	{
		stringtree_append_printf(tree, "unsigned native_end = string->len;");
	}
	
	stringtree_append_printf(tree, "if (native_end < native_start)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	native_end = native_start = 0;");
	stringtree_append_printf(tree, "}");
	
	stringtree_append_printf(tree, "unsigned len = native_end - native_start;");
	
	stringtree_append_printf(tree, "unsigned char* buffer = malloc(len);");
	
	stringtree_append_printf(tree, "memcpy(buffer, string->chars + native_start, len);");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	stringtree_append_printf(tree, "struct type_%u* result = func_%u(buffer, len);", super->type->id, new_id);
	
	unsigned free_list_id = function_queue_submit_free(shared->fqueue, this->string->type);
	stringtree_append_printf(tree, "func_%u(string);", free_list_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}















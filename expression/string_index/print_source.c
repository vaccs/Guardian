
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* string_index_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct type* environment)
{
	ENTER;
	
	assert(super->kind == ek_string_index);
	
	struct string_index_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* string_tree = expression_print_source(this->string, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* string = ", this->string->type->id);
	stringtree_append_tree(tree, string_tree);
	stringtree_append_printf(tree, ";");
	free_stringtree(string_tree);
	
	struct stringtree* index_tree = expression_print_source(this->index, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* index = ", this->index->type->id);
	stringtree_append_tree(tree, index_tree);
	stringtree_append_printf(tree, ";");
	free_stringtree(index_tree);
	
	stringtree_append_printf(tree, "unsigned native_index;");
		
	stringtree_append_printf(tree, ""
		"if (mpz_fits_uint_p(index->value) && (native_index = mpz_get_ui(index->value)) >= string->len)"
		"{"
			"fprintf(stderr, \"%%s: attempt to access element at "
				"index %%u in string %%u characters long!\", argv0, "
					"native_index, string->len);"
			"exit(1);"
		"}"
	"");
	
	stringtree_append_printf(tree, ""
		"unsigned char element = string->chars[native_index];"
	"");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* result = func_%u(memcpy(malloc(1), &element, 1), 1);"
	"", super->type->id, new_id);
	
	unsigned free_string_id = function_queue_submit_free(shared->fqueue, this->string->type);
	
	unsigned free_index_id = function_queue_submit_free(shared->fqueue, this->index->type);
	
	stringtree_append_printf(tree, ""
		"func_%u(string), func_%u(index);"
	"", free_string_id, free_index_id);
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}
















#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/function_queue/submit_print.h>

#include <type/print.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* dict_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_dict);
	
	struct stringtree* text = new_stringtree();
	
	struct dict_type* this = (void*) super;
	
	unsigned key_print_id = function_queue_submit_print(flookup, this->key);
	unsigned val_print_id = function_queue_submit_print(flookup, this->value);
	
	stringtree_append_printf(text, ""
		"void func_%u(const struct type_%u* this)"
		"{"
			"printf(\"{\");"
			
			"unsigned n = this->n;"
			
			"for (unsigned i = 0; i < n; i++)"
			"{"
				"if (i) printf(\", \");"
				"func_%u(this->data[i].key);"
				"printf(\": \");"
				"func_%u(this->data[i].value);"
			"}"
			
			"if (!n)"
			"{"
	"", func_id, super->id, key_print_id, val_print_id);
	
	struct stringtree* keytree = type_print2(this->key);
	struct stringtree* valtree = type_print2(this->value);
	
	stringtree_append_printf(text, "printf(\"<%%s: %%s>\", \"");
	stringtree_append_tree(text, keytree);
	stringtree_append_printf(text, "\", \"");
	stringtree_append_tree(text, valtree);
	stringtree_append_printf(text, "\");");
	
	stringtree_append_printf(text, ""
			"}"
			"printf(\"}\");"
		"}"
	"");
	
	free_stringtree(keytree);
	free_stringtree(valtree);
	
	EXIT;
	return text;
}


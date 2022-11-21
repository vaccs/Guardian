
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

struct stringtree* list_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_list);
	
	struct stringtree* text = new_stringtree();
	
	struct list_type* this = (void*) super;
	
	if (this->element_type->kind == tk_char)
	{
		stringtree_append_printf(text, ""
			"void func_%u(const struct type_%u* this)"
			"{"
				"printf(\"\\\"\");"
				""
				"for (unsigned i = 0, n = this->n; i < n; i++)"
				"{"
					"unsigned value = this->data[i]->value;"
					""
					"switch (value)"
					"{"
						"case ' ':"
						"case '~':"
						"case '`':"
						"case '!':"
						"case '@':"
						"case '#':"
						"case '$':"
						"case '%%':"
						"case '^':"
						"case '&':"
						"case '*':"
						"case '(':"
						"case ')':"
						"case '_':"
						"case '-':"
						"case '+':"
						"case '=':"
						"case '[':"
						"case ']':"
						"case '{':"
						"case '}':"
						"case ':':"
						"case ';':"
						"case '0' ... '9':"
						"case 'a' ... 'z':"
						"case 'A' ... 'Z':"
						"{"
							"printf(\"%%c\", value);"
							"break;"
						"}"
						""
						"default:"
						"{"
							"printf(\"\\\\x%%02hhX\", value);"
							"break;"
						"}"
					"}"
				"}"
				""
				"printf(\"\\\"\");"
			"}"
		"", func_id, super->id);
	}
	else
	{
		unsigned print_id = function_queue_submit_print(flookup, this->element_type);
		
		struct stringtree* subtree = type_print2(this->element_type);
		
		stringtree_append_printf(text, ""
			"void func_%u(const struct type_%u* this)"
			"{"
				"printf(\"[\");"
				
				"unsigned n = this->n;"
				
				"for (unsigned i = 0; i < n; i++)"
				"{"
					"if (i) printf(\", \");"
					"func_%u(this->data[i]);"
				"}"
				
				"if (!n)"
				"{"
		"", func_id, super->id, print_id);
		
		stringtree_append_printf(text, "printf(\"<%%s>\", \"");
		stringtree_append_tree(text, subtree);
		stringtree_append_printf(text, "\");");
		
		stringtree_append_printf(text, ""
				"}"
				
				"printf(\"]\");"
			"}"
		"");
		
		free_stringtree(subtree);
	}
	
	EXIT;
	return text;
}






















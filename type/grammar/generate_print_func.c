
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <list/named_type/foreach.h>

#include <named/type/struct.h>

#include <out/shared.h>
#include <out/function_queue/submit_print.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* grammar_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct stringtree* text = new_stringtree();
	
	struct grammar_type* this = (void*) super;
	
	stringtree_append_printf(text, ""
		"void func_%u(const struct type_%u* this)"
		"{"
	"", func_id, super->id);
	
	stringtree_append_printf(text, "printf(\"#%.*s(\");",
		this->name->len, this->name->chars);
	
	bool first = true;
	
	named_type_list_foreach(this->fields, ({
		void runme(struct named_type* field)
		{
			if (first)
			{
				stringtree_append_printf(text, "bool first = true;");
				first = false;
			}
			
			unsigned print_id = function_queue_submit_print(flookup, field->type);
			
			struct string* name = field->name;
			
			stringtree_append_printf(text, ""
				"if (this->$%.*s)"
				"{"
				"	if (first)"
				"		first = false;"
				"	else"
				"		printf(\", \");"
				"	"
				"	printf(\".%.*s = \");"
				"	"
				"	func_%u(this->$%.*s);"
				"}"
			"",
			name->len, name->chars,
			name->len, name->chars,
			print_id,
			name->len, name->chars);
		}
		runme;
	}));
	
	stringtree_append_printf(text, "printf(\")\");");
	
	stringtree_append_printf(text, ""
		"}"
	"");
	
	EXIT;
	return text;
}














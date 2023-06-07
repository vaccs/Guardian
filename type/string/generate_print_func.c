
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "generate_print_func.h"

struct stringtree* string_type_generate_print_func(
	struct type* super,
	unsigned func_id,
	struct function_queue* flookup)
{
	ENTER;
	
	assert(super->kind == tk_string);
	
	struct stringtree* text = new_stringtree();
	
	stringtree_append_printf(text, ""
		"void func_%u(const struct type_%u* this)"
		"{"
			"printf(\"\\\"\");"
			""
			"for (unsigned i = 0, n = this->len; i < n; i++)"
			"{"
				"unsigned value = this->chars[i];"
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
					"case '.':"
					"case ',':"
					"case '=':"
					"case '[':"
					"case ']':"
					"case '{':"
					"case '}':"
					"case ':':"
					"case ';':"
					"case '/':"
					"case '>':"
					"case '<':"
					"case '|':"
					"case '0' ... '9':"
					"case 'a' ... 'z':"
					"case 'A' ... 'Z':"
					"{"
						"printf(\"%%c\", value);"
						"break;"
					"}"
					""
					"case '\\\"':"
					"{"
						"printf(\"\\\\\\\"\");"
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
	
	EXIT;
	return text;
}







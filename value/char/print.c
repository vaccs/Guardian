
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print.h"

struct stringtree* char_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_char);
	
	struct stringtree* tree = new_stringtree();
	
	struct char_value* this = (void*) super;
	
	switch (this->value)
	{
		case '0' ... '9':
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case ':':
		case '+':
		case '*':
		case ' ':
		case '-':
		case '(':
		case ')':
		case '/':
		case '.':
		case '_':
			stringtree_append_printf(tree, "'%c'", this->value);
			break;
		
		case '\t':
			stringtree_append_printf(tree, "\\t");
			break;
		
		case '\n':
			stringtree_append_printf(tree, "\\n");
			break;
		
		case '\\':
			stringtree_append_printf(tree, "\\\\");
			break;
		
		default:
		{
			dpvc(this->value);
			TODO;
			break;
		}
	}
	
	EXIT;
	return tree;
}









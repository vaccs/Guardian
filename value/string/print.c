
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print.h"

struct stringtree* string_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_string);
	
	struct stringtree* tree = new_stringtree();
	
	struct string_value* this = (void*) super;
	
	stringtree_append_printf(tree, "\"");
	
	unsigned char code;
	
	for (unsigned i = 0, n = this->len; i < n; i++)
	{
		switch ((code = this->chars[i]))
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
			case '<':
			case '>':
			case '&':
			case ';':
			case '[':
			case ']':
				stringtree_append_printf(tree, "%c", code);
				break;
			
			case '\e':
				stringtree_append_printf(tree, "\\e");
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
			  printf("code == %u\n", code);
				dpvc(code);
				TODO;
				break;
			}
		}
	}
	
	stringtree_append_printf(tree, "\"");
	
	EXIT;
	return tree;
}









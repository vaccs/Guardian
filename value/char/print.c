
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void char_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_char);
	
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
			printf("'%c'", this->value);
			break;
		
		default:
		{
			dpvc(this->value);
			TODO;
			break;
		}
	}
	
	EXIT;
}


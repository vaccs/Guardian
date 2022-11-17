
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include "struct.h"
#include "print.h"

struct stringtree* variable_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_variable);
	
	struct variable_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct string* name = this->name;
	
	stringtree_append_printf(tree, "%.*s", name->len, name->chars);
	
	EXIT;
	return tree;
}


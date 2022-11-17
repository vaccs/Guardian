
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* fieldaccess_expression_print(
	struct expression* super)
{
	ENTER;
	
	
	assert(super->kind == ek_fieldaccess);
	
	struct stringtree* tree = new_stringtree();
	
	struct fieldaccess_expression* this = (void*) super;
	
	struct stringtree* subtree = expression_print2(this->object);
	
	stringtree_append_tree(tree, subtree);
	
	stringtree_append_printf(tree, ".%.*s", this->fieldname->len, this->fieldname->chars);
	
	free_stringtree(subtree);
	
	EXIT;
	return tree;
}


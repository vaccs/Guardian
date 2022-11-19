
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_string.h>

#include "struct.h"
#include "print.h"

struct stringtree* grammar_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct stringtree* tree = new_stringtree();
	
	struct grammar_type* this = (void*) super;
	
	stringtree_append_string(tree, this->name);
	
	EXIT;
	return tree;
}


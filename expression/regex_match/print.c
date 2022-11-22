
#include <stdio.h>
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
#include <stringtree/append_printf.h>
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/free.h>*/

#include <expression/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* regex_match_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_regex_match);
	
	struct regex_match_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->expression);
	
	stringtree_append_printf(tree, " =~ /regex/");
	
	EXIT;
	return tree;
}


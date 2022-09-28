
#include <debug.h>

#include <named/zebu_expression/new.h>

#include "parse.h"
#include "declare.h"

void process_declare(
	struct avl_tree_t* grammar,
	struct avl_tree_t* declares,
	struct zebu_value_declare* declare)
{
	ENTER;
	
	assert(declare->name);
	assert(declare->expression);
	
	struct string* name = new_string_from_token(declare->name);
	
	if (avl_search(grammar, &name) || avl_search(declares, &name))
	{
		TODO;
		exit(1);
	}
	
	avl_insert(declares, new_named_zebu_expression(name, declare->expression));
	
	free_string(name);
	
	EXIT;
}


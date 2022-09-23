
#include <debug.h>

#include <named/zebu_expression/new.h>

#include "parser.h"
#include "declare.h"

void process_declare(
	struct avl_tree_t* grammar,
	struct avl_tree_t* declares,
	struct zebu_entry* entry)
{
	ENTER;
	
	assert(entry->name);
	assert(entry->expression);
	
	struct string* name = new_string_from_token(entry->name);
	
	if (avl_search(grammar, &name) || avl_search(declares, &name))
	{
		TODO;
		exit(1);
	}
	
	avl_insert(declares, new_named_zebu_expression(name, entry->expression));
	
	free_string(name);
	
	EXIT;
}


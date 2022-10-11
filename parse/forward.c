
#include <debug.h>

#include <named/zebu_type/new.h>

#include "parse.h"
#include "forward.h"

void process_forward(
	struct avl_tree_t* grammar,
	struct avl_tree_t* forwards,
	struct avl_tree_t* declares,
	struct zebu_forward_directive* forward)
{
	ENTER;
	
	assert(forward->name);
	assert(forward->type);
	
	struct string* name = new_string_from_token(forward->name);
	
	if (false
		|| avl_search(grammar, &name)
		|| avl_search(forwards, &name)
		|| avl_search(declares, &name))
	{
		TODO;
		exit(1);
	}
	
	avl_insert(forwards, new_named_zebu_type(name, forward->type));
	
	free_string(name);
	
	EXIT;
}

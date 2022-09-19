
#include <debug.h>

#include <named/grammar/new.h>

#include "../struct.h"

#include "grammar.h"

void scope_declare_grammar(
	struct scope* this,
	struct string* name,
	struct gegex* grammar)
{
	ENTER;
	
	struct named_grammar* ngrammar = new_named_grammar(name, grammar);
	
	struct avl_node_t* node = avl_insert(this->named_grammar, ngrammar);
	
	if (!node)
	{
		TODO;
	}
	
	EXIT;
}


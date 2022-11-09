
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <list/raw_declaration/append.h>

#include "declaration/new.h"
#include "declaration/free.h"

#include "parse.h"
#include "declare.h"

void process_declare(
	struct avl_tree_t* grammar,
	struct raw_declaration_list* declarations,
	struct zebu_value_declare* declare)
{
	ENTER;
	
	assert(declare->name);
	assert(declare->expression);
	
	struct string* name = new_string_from_token(declare->name);
	
	struct raw_declaration* declaration = new_raw_declaration(
		name, declare->expression);
	
	raw_declaration_list_append(declarations, declaration);
	
	free_raw_declaration(declaration);
	
	free_string(name);
	
	EXIT;
}



















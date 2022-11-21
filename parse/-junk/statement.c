
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <string/new.h>
#include <string/free.h>

#include <list/raw_statement/append.h>

#include "raw_statement/new.h"
#include "raw_statement/free.h"

#include "statement.h"

void process_statement(
	struct avl_tree_t* grammar,
	struct raw_statement_list* statements,
	struct zebu_statement* zstatement)
{
	ENTER;
	
	TODO;
	#if 0
	assert(zstatement->expression);
	
	else if (zstatement->name)
	{
	}
	else if (zstatement->print)
	{
		struct raw_statement* statement = new_raw_print(zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else
	{
		struct raw_statement* statement = new_raw_print(zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	#endif
	
	EXIT;
}

















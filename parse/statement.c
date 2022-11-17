
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
	
	assert(zstatement->expression);
	
	if (zstatement->error)
	{
		struct raw_statement* statement = new_raw_assertion(ak_error, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else if (zstatement->warning)
	{
		struct raw_statement* statement = new_raw_assertion(ak_warning, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else if (zstatement->note)
	{
		struct raw_statement* statement = new_raw_assertion(ak_note, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else if (zstatement->name)
	{
		struct string* name = new_string_from_token(zstatement->name);
		
		struct raw_statement* statement = new_raw_declaration(name, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
		
		free_string(name);
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
	
	EXIT;
}

















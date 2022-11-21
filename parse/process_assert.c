
#include <assert.h>

#include <debug.h>

#include <list/raw_statement/append.h>

#include "parse.h"

#include "raw_statement/new.h"
#include "raw_statement/free.h"

#include "process_assert.h"

void process_assert(
	struct raw_statement_list* statements,
	struct zebu_assert_statement* zstatement)
{
	ENTER;
	
	if (zstatement->error)
	{
		struct raw_statement* statement = new_raw_assertion(
			zstatement->error->line,
			ak_error, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else if (zstatement->warning)
	{
		struct raw_statement* statement = new_raw_assertion(
			zstatement->warning->line,
			ak_warning, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else if (zstatement->note)
	{
		struct raw_statement* statement = new_raw_assertion(
			zstatement->note->line,
			ak_note, zstatement->expression);
		
		raw_statement_list_append(statements, statement);
		
		free_raw_statement(statement);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}


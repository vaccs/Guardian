
#include <debug.h>

#include <list/raw_statement/append.h>

#include "parse.h"

#include "raw_statement/new.h"
#include "raw_statement/free.h"

#include "process_print.h"

void process_print(
	struct raw_statement_list* statements,
	struct zebu_print_statement* zstatement)
{
	ENTER;
	
	struct raw_statement* statement = new_raw_print(zstatement->expression);
	
	raw_statement_list_append(statements, statement);
	
	free_raw_statement(statement);
	
	EXIT;
}


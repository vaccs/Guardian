
#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <list/raw_statement/append.h>

#include "parse.h"

#include "raw_statement/new.h"
#include "raw_statement/free.h"

#include "process_declare.h"

void process_declare(
	struct raw_statement_list* statements,
	struct zebu_declare_statement* zstatement)
{
	ENTER;
	
	struct string* name = new_string_from_token(zstatement->name);
	
	struct raw_statement* statement = new_raw_declaration(
	    zstatement->startline,
		name, zstatement->expression);
	
	raw_statement_list_append(statements, statement);
	
	free_raw_statement(statement);
	
	free_string(name);
	
	EXIT;
}


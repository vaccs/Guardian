
#include "../struct.h"

struct parse_statement
{
	struct statement super;
	
	struct expression* expression;
	
	struct string* grammar_name;
	
	struct gegex* grammar;
	
	struct yacc_state* ystate;
	
	unsigned start_id, grammar_id;
};


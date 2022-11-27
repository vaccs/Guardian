
struct lex;
struct yacc_state;
struct statement_list;

void lex_minimize_lexer(
	struct lex* this,
	struct statement_list* statements);
	


struct expression;
struct gegex;

struct statement* new_parse_statement(
	unsigned line,
	struct expression* expression,
	struct string* grammar_name,
	struct gegex* grammar);

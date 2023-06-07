
struct string;
struct expression;

struct statement* new_declare_statement(
    unsigned line,
	struct string* name,
	struct expression* expression);


struct string;
struct expression;

struct statement* new_declare_statement(
	struct string* name,
	struct expression* expression);

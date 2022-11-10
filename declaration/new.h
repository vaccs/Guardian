
struct string;
struct expression;

struct declaration* new_declaration(
	struct string* name,
	struct expression* expression);

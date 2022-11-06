
struct string;
struct zebu_expression;

struct named_zebu_expression* new_named_zebu_expression(
	struct string* name,
	struct zebu_expression* expression);
	

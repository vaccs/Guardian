
struct zebu_match_expression;
struct type_check;
struct type_check_scope;

struct type* determine_type_of_match_expression(
	struct zebu_match_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope);

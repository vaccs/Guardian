
struct type_cache;
struct type_check_scope;
struct zebu_match_expression;

struct expression* specialize_match_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_match_expression* zexpression);




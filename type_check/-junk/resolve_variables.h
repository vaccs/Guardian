
struct unresolved;
struct type_cache;
struct zebu_expression;

void resolve_variables(
	struct unresolved* unresolved,
	struct type_cache* tcache,
	struct zebu_expression* expression);

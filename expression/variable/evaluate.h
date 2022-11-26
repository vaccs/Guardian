
struct scope;
struct type_cache;

struct value* variable_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment);

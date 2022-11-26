
struct type_cache;
struct scope;

struct value* logical_and_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment);

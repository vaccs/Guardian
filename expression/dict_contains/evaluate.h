
struct scope;

struct value* dict_contains_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment);

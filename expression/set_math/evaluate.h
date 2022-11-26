
struct type_cache;
struct scope;

struct value* set_math_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment);

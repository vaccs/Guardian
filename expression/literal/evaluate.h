
struct type_cache;
struct expression;
struct scope;

struct value* literal_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment);

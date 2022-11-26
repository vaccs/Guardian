
struct type_cache;
struct expression;
struct value;
struct scope;

struct value* expression_evaluate(
	struct type_cache* tcache,
	struct expression* this,
	struct value* environment);

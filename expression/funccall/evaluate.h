
struct expression;
struct scope;

struct value* funccall_expression_evaluate(
	struct expression* super,
	struct scope* scope);

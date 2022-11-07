
struct scope;
struct expression;

struct value* tuple_expression_evaluate(
	struct expression* this,
	struct scope* scope);

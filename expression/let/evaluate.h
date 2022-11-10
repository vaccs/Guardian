
struct scope;
struct expression;

struct value* let_expression_evaluate(
	struct expression* this,
	struct scope* scope);

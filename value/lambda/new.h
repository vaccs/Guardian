
struct type;
struct parameter_list;
struct scope;
struct expression;

struct value* new_lambda_value(
	struct type* type,
	struct parameter_list* parameters,
	struct scope* scope,
	struct expression* body);

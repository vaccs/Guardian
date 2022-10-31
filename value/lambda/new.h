

struct value* new_lambda_value(
	struct type* type,
	unsigned id,
	struct parameter_list* parameters,
	struct scope* captured,
	struct expression* body);

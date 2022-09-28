
struct value* new_lambda_value(
	struct type_cache* tcache,
	struct parameter_list* parameters,
	struct parameter_list* captured,
	struct expression* body);

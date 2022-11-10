
struct capture_list;

struct expression* new_lambda_expression(
	struct type* type,
	struct parameter_list* parameters,
	struct type* environment,
	struct expression* body);
	
	

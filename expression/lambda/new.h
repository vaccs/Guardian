
struct named_type_list;
struct parameter_list;
struct capture_list;

struct expression* new_lambda_expression(
	struct type* type,
	struct named_type_list* parameters,
	struct expression* body);
	

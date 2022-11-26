
struct expression_list;

struct expression* new_list_init_expression(
	struct type* type,
	struct expression_list* elements);

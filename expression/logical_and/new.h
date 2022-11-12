
struct type_cache;

struct expression* new_logical_and_expression(
	struct type* type,
	struct expression* left,
	struct expression* right);

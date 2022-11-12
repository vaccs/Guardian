
struct type_cache;

struct expression* new_implication_expression(
	struct type* type,
	struct expression* left,
	struct expression* right);

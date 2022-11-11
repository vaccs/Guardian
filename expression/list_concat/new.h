
struct type_cache;

struct expression* new_list_concat_expression(
	struct type* type,
	struct expression* left,
	struct expression* right);

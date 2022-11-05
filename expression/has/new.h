
struct type_cache;
struct string;

struct expression* new_has_expression(
	struct type_cache* tcache,
	struct expression* object,
	struct string* fieldname);

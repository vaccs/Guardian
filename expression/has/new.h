
struct type;
struct type_cache;
struct string;

struct expression* new_has_expression(
	struct type* type,
	struct expression* object,
	struct string* fieldname);

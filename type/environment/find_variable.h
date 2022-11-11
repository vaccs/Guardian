
struct environment_type;
struct string;
struct type;

unsigned environment_type_find_variable(
	struct environment_type* this,
	struct string* name,
	struct type* type);

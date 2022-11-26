
struct type;
struct string_value;
struct list_value;

struct value* string_concat_run(
	struct type* type,
	struct string_value* left,
	struct string_value* right);

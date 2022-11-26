
struct string_value;
struct type;
struct value;
struct list_value;

struct value* string_contains_run(
	struct type* type,
	struct string_value* substring,
	struct string_value* string);

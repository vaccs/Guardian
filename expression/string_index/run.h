
struct string_value;
struct type;
struct int_value;
struct list_value;

struct value* string_index_run(
	struct type* type,
	struct string_value* list,
	struct int_value* index);

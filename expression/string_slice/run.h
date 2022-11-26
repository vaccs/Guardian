
struct string_value;
struct type;
struct int_value;
struct list_value;

struct value* string_slice_run(
	struct type* type,
	struct string_value* string,
	struct int_value* startindex,
	struct int_value*   endindex);


struct type;
struct tuple_value;

struct value* tuple_concat_run(
	struct type* type,
	struct tuple_value* left,
	struct tuple_value* right);

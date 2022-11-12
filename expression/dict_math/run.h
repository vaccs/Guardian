
struct type;
struct dict_value;

struct value* dict_math_concat_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right);

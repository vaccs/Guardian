
struct type;
struct dict_value;

struct value* dict_math_union_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right);
	
struct value* dict_math_intersect_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right);
	
struct value* dict_math_symdifference_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right);
	
struct value* dict_math_difference_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right);

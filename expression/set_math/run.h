
struct type;
struct set_value;

struct value* set_math_union_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right);
	
struct value* set_math_intersect_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right);
	
struct value* set_math_symdifference_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right);
	
struct value* set_math_difference_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right);

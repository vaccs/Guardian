
struct type;
struct int_value;

struct value* int_math_negate_run(
	struct type* type,
	struct int_value* left);
	
struct value* int_math_bitnegate_run(
	struct type* type,
	struct int_value* left);

struct value* int_math_add_run(
	struct type* type,
	struct int_value* left_value,
	struct int_value* right_value);
	
struct value* int_math_sub_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_expo_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
	
struct value* int_math_lshift_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_rshift_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_bitand_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_bitor_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_bitxor_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_mult_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_qdiv_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);
	
struct value* int_math_rdiv_run(
	struct type* type,
	struct int_value* left,
	struct int_value* right);

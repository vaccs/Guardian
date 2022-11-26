
struct float_value;
struct type;
struct string_value;

struct value* int_form_run_on_float(
	struct type* type,
	struct float_value* value);

struct value* int_form_run_on_string(
	struct type* type,
	struct string_value* value);

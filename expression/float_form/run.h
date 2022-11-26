
struct string_value;
struct type;
struct int_value;

struct value* float_form_run_on_int(
	struct type* type,
	struct int_value* value);
	
struct value* float_form_run_on_string(
	struct type* type,
	struct string_value* value);

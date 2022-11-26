
struct lambda_value;

struct value_list;

struct value* crossmap_form_run(
	struct type_cache* tcache,
	struct type* type,
	struct lambda_value* lambda,
	struct value_list* args);

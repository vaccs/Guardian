
struct lambda_value;

struct value_list;

struct value* map_form_run(
	struct type* type,
	struct lambda_value* lambda,
	struct value_list* args);

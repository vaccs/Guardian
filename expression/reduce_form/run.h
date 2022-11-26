
struct list_value;

struct type;

struct type_cache;

struct lambda_value;

struct value_list;

struct value* reduce_form_run(
	struct type_cache* tcache,
	struct type* type,
	struct lambda_value* lambda,
	struct list_value* list,
	struct value* initial);

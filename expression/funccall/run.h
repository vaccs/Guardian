
struct value;
struct type_cache;
struct environment_value;
struct lambda_value;
struct value_list;

struct value* funccall_run(
	struct type_cache* tcache,
	struct lambda_value* lambda,
	struct value_list* arguments);

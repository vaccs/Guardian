
struct lambda_value;
struct value_list;

struct value* funccall_run(
	struct lambda_value* this,
	struct value_list* arguments);

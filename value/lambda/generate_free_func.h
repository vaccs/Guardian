
struct lambda_value;
struct out_shared;

struct stringtree* lambda_value_generate_free_func(
	struct lambda_value* this,
	unsigned func_id,
	struct out_shared* shared);

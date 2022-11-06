
struct lambda_value;

struct stringtree* lambda_value_generate_new_func(
	struct lambda_value* this,
	unsigned funcid,
	struct out_shared* shared);

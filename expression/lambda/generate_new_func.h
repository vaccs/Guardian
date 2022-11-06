
struct lambda_expression;

struct stringtree* lambda_expression_generate_new_func(
	struct lambda_expression* this,
	unsigned func_id,
	struct out_shared* shared);


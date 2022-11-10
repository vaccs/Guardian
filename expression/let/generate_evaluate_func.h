
struct let_expression;
struct out_shared;

struct stringtree* let_expression_generate_evaluate_func(
	struct let_expression* this,
	unsigned func_id,
	struct out_shared* shared);

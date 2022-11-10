
struct out_shared;
struct let_expression;

struct stringtree* let_expression_generate_new_func(
	struct let_expression* this,
	unsigned func_id,
	struct out_shared* shared);


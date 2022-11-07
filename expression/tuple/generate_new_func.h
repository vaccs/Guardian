
struct out_shared;
struct tuple_expression;

struct stringtree* tuple_expression_generate_new_func(
	struct tuple_expression* this,
	unsigned func_id,
	struct out_shared* shared);


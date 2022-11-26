
struct out_shared;
struct tuple_init_expression;

struct stringtree* tuple_init_expression_generate_new_func(
	struct tuple_init_expression* this,
	unsigned func_id,
	struct out_shared* shared);


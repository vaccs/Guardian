
struct type_queue;
struct tuple_init_expression;
struct subtype_queue;

struct stringtree* tuple_init_expression_generate_generate_typedef(
	struct tuple_init_expression* this,
	struct subtype_queue* stqueue,
	struct type_queue* tqueue);

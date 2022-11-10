
struct type_queue;
struct let_expression;
struct subtype_queue;

struct stringtree* let_expression_generate_generate_typedef(
	struct let_expression* this,
	struct subtype_queue* stqueue,
	struct type_queue* tqueue);


struct type_queue;
struct lambda_expression;
struct subtype_queue;

struct stringtree* lambda_expression_generate_generate_typedef(
	struct lambda_expression* this,
	struct subtype_queue* stqueue,
	struct type_queue* tqueue);

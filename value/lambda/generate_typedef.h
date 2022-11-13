
struct lambda_value;
struct subtype_queue;
struct type_queue;

struct stringtree* lambda_value_generate_generate_typedef(
	struct lambda_value* this,
	struct subtype_queue* squeue,
	struct type_queue* tqueue);

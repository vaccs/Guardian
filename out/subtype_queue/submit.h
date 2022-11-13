
struct subtype_queue;
struct lambda_expression;

void subtype_queue_submit(
	struct subtype_queue* this,
	struct lambda_expression* lexpression);

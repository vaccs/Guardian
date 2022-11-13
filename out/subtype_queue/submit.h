
struct lambda_value;
struct subtype_queue;
struct lambda_expression;

void subtype_queue_submit_value(
	struct subtype_queue* this,
	struct lambda_value* value);
	
void subtype_queue_submit_expression(
	struct subtype_queue* this,
	struct lambda_expression* lexpression);

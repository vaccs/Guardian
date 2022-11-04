
struct function_queue;
struct lambda_expression;
struct lambda_value;

unsigned function_queue_submit_lambda_expression_evaluate(
	struct function_queue* this,
	struct lambda_expression* lexpression);
	
unsigned function_queue_submit_lambda_value_evaluate(
	struct function_queue* this,
	struct lambda_value* lvalue);
	

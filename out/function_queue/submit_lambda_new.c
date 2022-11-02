
#include <debug.h>

#include "funcdata/struct.h"
#include "funcdata/new.h"

#include "struct.h"
#include "submit_lambda_new.h"

unsigned function_queue_submit_lambda_value_new(
	struct function_queue* this,
	struct lambda_value* lvalue)
{
	unsigned id;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->queued, &(struct funcdata) {
		.kind = fk_lambda_new,
		.lvalue = lvalue,
	});
	
	if (node)
	{
		struct funcdata* fdata = node->item;
		
		id = fdata->id;
	}
	else
	{
		struct funcdata* fdata = new_funcdata(fk_lambda_new, NULL, NULL, lvalue, id = this->next++);
		
		quack_append(this->todo, fdata);
		
		avl_insert(this->queued, fdata);
	}
	
	EXIT;
	return id;
}


unsigned function_queue_submit_lambda_expression_new(
	struct function_queue* this,
	struct lambda_expression* lexpression)
{
	unsigned id;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->queued, &(struct funcdata) {
		.kind = fk_lambda_new,
		.lexpression = lexpression,
	});
	
	if (node)
	{
		struct funcdata* fdata = node->item;
		
		id = fdata->id;
	}
	else
	{
		struct funcdata* fdata = new_funcdata(fk_lambda_new, NULL, lexpression, NULL, id = this->next++);
		
		quack_append(this->todo, fdata);
		
		avl_insert(this->queued, fdata);
	}
	
	EXIT;
	return id;
}










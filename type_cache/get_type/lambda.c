
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <type/lambda/struct.h>
#include <type/lambda/new.h>

#include "../struct.h"

#include "lambda.h"

struct type* type_cache_get_lambda_type(
	struct type_cache* this,
	struct type_list* parameters,
	struct type* rettype)
{
	struct type* retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct lambda_type){
		.super.kind = tk_lambda,
		.parameters = parameters,
		.rettype = rettype,
	});
	
	if (node)
	{
		retval = node->item;
	}
	else
	{
		struct type* lambda = new_lambda_type(this->next++, parameters, rettype);
		
		avl_insert(this->tree, lambda);
		
		retval = lambda;
	}
	
	EXIT;
	return retval;
}

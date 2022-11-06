
#include <debug.h>

#include <type/struct.h>
#include <type/generate_new_func.h>
#include <type/generate_new_forward.h>
#include <type/generate_inc_func.h>
#include <type/generate_inc_forward.h>
#include <type/generate_compare_func.h>
#include <type/generate_compare_forward.h>
#include <type/generate_free_func.h>
#include <type/generate_free_forward.h>

#include <type/list/generate_index_func.h>
#include <type/list/generate_append_func.h>

#include <stringtree/prepend_tree.h>

#include <expression/lambda/generate_new_func.h>
#include <expression/lambda/generate_evaluate_func.h>
#include <expression/lambda/generate_free_func.h>

#include <value/lambda/generate_new_func.h>
#include <value/lambda/generate_evaluate_func.h>

#include "funcdata/struct.h"

#include "struct.h"
#include "process.h"

void function_queue_process(
	struct function_queue* this,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	while (quack_is_nonempty(this->todo))
	{
		struct funcdata* fdata = quack_pop(this->todo);
		
		struct stringtree* subtext = NULL;
		
		if (avl_search(this->done, fdata))
		{
			switch (fdata->kind)
			{
				case fk_new:
					subtext = type_generate_new_forward(fdata->type, fdata->id);
					break;
				
				case fk_inc:
					subtext = type_generate_inc_forward(fdata->type, fdata->id);
					break;
				
				case fk_compare:
					subtext = type_generate_compare_forward(fdata->type, fdata->id);
					break;
				
				case fk_free:
					subtext = type_generate_free_forward(fdata->type, fdata->id);
					break;
				
				default:
				{
					dpv(fdata->kind);
					TODO;
					break;
				}
			}
		}
		else
		{
			switch (fdata->kind)
			{
				case fk_new:
					dputs("fk_new");
					dpv(fdata->type);
					subtext = type_generate_new_func(fdata->type, fdata->id, this);
					break;
				
				case fk_inc:
					dputs("fk_inc");
					subtext = type_generate_inc_func(fdata->type, fdata->id);
					break;
				
				case fk_index:
					dputs("fk_index");
					assert(fdata->type->kind == tk_list);
					subtext = list_type_generate_index_func((void*) fdata->type, fdata->id, shared);
					break;
				
				case fk_append:
					dputs("fk_append");
					assert(fdata->type->kind == tk_list);
					subtext = list_type_generate_append_func((void*) fdata->type, fdata->id, shared);
					break;
				
				case fk_compare:
					dputs("fk_compare");
					subtext = type_generate_compare_func(fdata->type, fdata->id, this);
					break;
				
				case fk_free:
					dputs("fk_free");
					subtext = type_generate_free_func(fdata->type, fdata->id, this);
					break;
				
				case fk_lambda_new:
				{
					dputs("fk_lambda_new");
					if (fdata->lexpression)
						subtext = lambda_expression_generate_new_func(fdata->lexpression, fdata->id, shared);
					else if (fdata->lvalue)
						subtext = lambda_value_generate_new_func(fdata->lvalue, fdata->id, shared);
					else
					{
						TODO;
					}
					break;
				}
				
				case fk_lambda_evaluate:
				{
					dputs("fk_lambda_evaluate");
					if (fdata->lexpression)
						subtext = lambda_expression_generate_evaluate_func(fdata->lexpression, fdata->id, shared);
					else if (fdata->lvalue)
						subtext = lambda_value_generate_evaluate_func(fdata->lvalue, fdata->id, shared);
					else
					{
						TODO;
					}
					break;
				}
				
				case fk_lambda_free:
				{
					dputs("fk_lambda_free");
					if (fdata->lexpression)
						subtext = lambda_expression_generate_free_func(fdata->lexpression, fdata->id, shared);
					else if (fdata->lvalue)
					{
						TODO;
					}
					else
					{
						TODO;
					}
					break;
				}
				
				default:
					dpv(fdata->kind);
					TODO;
					break;
			}
			
			avl_insert(this->done, fdata);
		}
		
		avl_delete(this->queued, fdata);
		
		stringtree_prepend_tree(text, subtext);
		
		free_stringtree(subtext);
	}
	
	this->text = text;
	
	EXIT;
}

















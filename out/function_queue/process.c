
#include <debug.h>

#include <type/struct.h>
#include <type/generate_new_func.h>
#include <type/generate_inc_func.h>
#include <type/generate_compare_func.h>
#include <type/list/generate_index_func.h>
#include <type/generate_free_func.h>

#include <stringtree/prepend_tree.h>

#include <value/lambda/generate_new_func.h>
#include <value/lambda/generate_evaluate_func.h>

#include "funcdata/struct.h"

#include "struct.h"
#include "process.h"

void function_queue_process(
	struct function_queue* this)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	while (quack_is_nonempty(this->todo))
	{
		struct funcdata* fdata = quack_pop(this->todo);
		
		if (avl_search(this->done, fdata))
		{
			TODO;
		}
		else
		{
			struct stringtree* func = NULL;
			
			switch (fdata->kind)
			{
				case fk_new:
					dputs("fk_new");
					dpv(fdata->type);
					func = type_generate_new_func(fdata->type, fdata->id, this);
					break;
				
				case fk_inc:
					dputs("fk_inc");
					func = type_generate_inc_func(fdata->type, fdata->id);
					break;
				
				case fk_compare:
					dputs("fk_compare");
					func = type_generate_compare_func(fdata->type, fdata->id, this);
					break;
				
				case fk_free:
					dputs("fk_free");
					func = type_generate_free_func(fdata->type, fdata->id, this);
					break;
				
				case fk_index:
					dputs("fk_index");
					assert(fdata->type->kind == tk_list);
					func = list_type_generate_index_func((void*) fdata->type, fdata->id, this);
					break;
				
				case fk_lambda_new:
				{
					dputs("fk_lambda_new");
					if (fdata->lexpression)
					{
						TODO;
					}
					else if (fdata->lvalue)
					{
						func = lambda_value_generate_new_func(fdata->lvalue, fdata->id, this);
					}
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
					{
						TODO;
					}
					else if (fdata->lvalue)
					{
						func = lambda_value_generate_evaluate_func(fdata->lvalue, fdata->id, this);
					}
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
					{
						TODO;
					}
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
			
			stringtree_prepend_tree(text, func);
			
			avl_insert(this->done, fdata);
			
			avl_delete(this->queued, fdata);
			
			free_stringtree(func);
		}
	}
	
	this->text = text;
	
	EXIT;
}

















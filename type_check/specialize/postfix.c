
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <parse/parse.h>

#include <type/struct.h>
#include <type/lambda/struct.h>
#include <type/print.h>

#include <string/new.h>
#include <string/free.h>

#include <type/grammar/get_field.h>

#include <list/type/struct.h>

#include <list/expression/new.h>
#include <list/expression/append.h>
#include <list/expression/free.h>

#include <type/list/struct.h>

#include <type/dict/struct.h>

#include <list/expression/struct.h>

#include <list/value/append.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/stream.h>
#include <stringtree/free.h>

#include <list/value/new.h>

#include <value/struct.h>

#include <expression/literal/new.h>

#include <list/value/free.h>

#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/funccall/run.h>
#include <expression/funccall/new.h>
#include <expression/fieldaccess/new.h>
#include <expression/dict_index/run.h>
#include <expression/dict_index/new.h>
#include <expression/list_index/run.h>
#include <expression/list_index/new.h>
#include <expression/dict_index/new.h>
#include <expression/list_slice/new.h>
#include <expression/string_slice/run.h>
#include <expression/string_slice/new.h>
#include <expression/string_index/new.h>
#include <expression/string_index/run.h>
#include <expression/free.h>

#include <type/tuple/struct.h>

#include <value/inc.h>
#include <value/tuple/struct.h>
#include <list/value/struct.h>

#include <expression/tuple_index/new.h>

#include "expression.h"
#include "primary/primary.h"
#include "postfix.h"

struct expression* specialize_postfix_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_postfix_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_primary_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->sub)
	{
		struct expression* sub = specialize_postfix_expression(tcache, scope, zexpression->sub);
		
		if (zexpression->slice)
		{
			struct expression* startindex = NULL;
			struct expression* endindex = NULL;
			
			if (zexpression->startindex)
			{
				startindex = specialize_expression(tcache, scope, zexpression->startindex);
				
				if (startindex->type->kind != tk_int)
				{
					TODO;
					exit(1);
				}
			}
			
			if (zexpression->endindex)
			{
				endindex = specialize_expression(tcache, scope, zexpression->endindex);
				
				if (endindex->type->kind != tk_int)
				{
					TODO;
					exit(1);
				}
			}
			
			switch (sub->type->kind)
			{
				case tk_string:
				{
					if (true
						&& sub->kind == ek_literal
						&& (!startindex || startindex->kind == ek_literal)
						&& (!  endindex ||   endindex->kind == ek_literal))
					{
						struct literal_expression* sublit = (void*) sub;
						
						struct string_value* string = (void*) sublit->value;
						
						struct int_value* startindex_int = NULL;
						struct int_value*   endindex_int = NULL;
						
						if (startindex)
						{
							startindex_int = (void*) ((struct literal_expression*) startindex)->value;
						}
						
						if (endindex)
						{
							endindex_int = (void*) ((struct literal_expression*) endindex)->value;
						}
						
						struct value* value = string_slice_run(sub->type, string, startindex_int, endindex_int);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_string_slice_expression(sub->type, sub, startindex, endindex);
					}
					break;
				}
				
				case tk_list:
				{
					if (true
						&& sub->kind == ek_literal
						&& (!startindex || startindex->kind == ek_literal)
						&& (!  endindex ||   endindex->kind == ek_literal))
					{
						TODO;
					}
					else
					{
						retval = new_list_slice_expression(sub->type, sub, startindex, endindex);
					}
					break;
				}
				
				default:
				{
					TODO;
					exit(1);
				}
			}
			
			free_expression(startindex);
			free_expression(endindex);
		}
		else if (zexpression->index)
		{
			struct expression* index = specialize_expression(tcache, scope, zexpression->index);
			
			switch (sub->type->kind)
			{
				case tk_string:
				{
					if (index->type->kind != tk_int)
					{
						TODO;
						exit(1);
					}
					
					if (sub->kind == ek_literal && index->kind == ek_literal)
					{
						struct literal_expression* sublit = (void*) sub;
						struct literal_expression* idxlit = (void*) index;
						
						struct string_value* string = (void*) sublit->value;
						struct int_value* index = (void*) idxlit->value;
						
						struct value* value = string_index_run(sub->type, string, index);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_string_index_expression(sub->type, sub, index);
					}
					break;
				}
				
				case tk_list:
				{
					struct list_type* ltype = (void*) sub->type;
					
					if (index->type->kind != tk_int)
					{
						TODO;
						exit(1);
					}
					
					if (sub->kind == ek_literal && index->kind == ek_literal)
					{
						struct literal_expression* sublit = (void*) sub;
						struct literal_expression* idxlit = (void*) index;
						
						struct list_value* list = (void*) sublit->value;
						struct int_value* index = (void*) idxlit->value;
						
						struct value* value = list_index_run(ltype->element_type, list, index);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_list_index_expression(ltype->element_type, sub, index);
					}
					break;
				}
				
				case tk_dict:
				{
					struct dict_type* dtype = (void*) sub->type;
					
					if (dtype->key != index->type)
					{
						TODO;
						#if 0
						struct stringtree* tree = new_stringtree();
						
						stringtree_append_printf(tree,
							"%s: incompatible type for index in dict-index "
							"expression: '", argv0);
						
						{
							struct stringtree* subtree = type_print2(index->type);
							stringtree_append_tree(tree, subtree);
							free_stringtree(subtree);
						}
						
						stringtree_append_printf(tree, "' on a dict of type '");
							
						{
							struct stringtree* subtree = type_print2(sub->type);
							stringtree_append_tree(tree, subtree);
							free_stringtree(subtree);
						}
						
						stringtree_append_printf(tree, "'!\n");
						
						stringtree_stream(tree, stderr);
						exit(1);
						#endif
					}
					
					if (sub->kind == ek_literal && index->kind == ek_literal)
					{
						struct literal_expression* sublit = (void*) sub;
						struct literal_expression* idxlit = (void*) index;
						
						struct dict_value* dict = (void*) sublit->value;
						
						struct value* value = dict_index_run(dict, idxlit->value);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_dict_index_expression(dtype->value, sub, index);
					}
					break;
				}
				
				default:
					TODO;
					break;
			}
			
			free_expression(index);
		}
		else if (zexpression->field)
		{
			if (sub->type->kind != tk_grammar)
			{
				struct stringtree* tree = new_stringtree();
				
				stringtree_append_printf(tree,
					"%s: incompatible type for field-index expression: '", argv0);
				
				{
					struct stringtree* subtree = type_print2(sub->type);
					stringtree_append_tree(tree, subtree);
					free_stringtree(subtree);
				}
				
				stringtree_append_printf(tree, "'!\n");
				
				stringtree_stream(tree, stderr);
				exit(1);
			}
			
			struct grammar_type* subtype = (void*) sub->type;
			
			struct string* fieldname = new_string_from_token(zexpression->field);
			
			struct type* fieldtype = grammar_type_get_field(subtype, fieldname);
			
			if (!fieldtype)
			{
				TODO;
				exit(1);
			}
			
			retval = new_fieldaccess_expression(fieldtype, sub, fieldname);
			
			free_string(fieldname);
		}
		else if (zexpression->tupleindex)
		{
			if (sub->type->kind != tk_tuple)
			{
				TODO;
				exit(1);
			}
			
			struct tuple_type* tupletype = (void*) sub->type;
			
			errno = 0;
			
			char* m;
			long index = strtol((char*) zexpression->tupleindex->data, &m, 0);
			
			if (errno || *m)
			{
				TODO;
				exit(1);
			}
			
			dpv(index);
			
			if (0 <= index && index < tupletype->subtypes->n)
			{
				if (sub->kind == ek_literal)
				{
					struct literal_expression* sublit = (void*) sub;
					
					struct tuple_value* tupval = (void*) sublit->value;
					
					struct value* value = inc_value(tupval->subvalues->data[index]);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					struct type* type = tupletype->subtypes->data[index];
					
					retval = new_tuple_index_expression(type, sub, index);
				}
			}
			else
			{
				TODO;
			}
		}
		else if (zexpression->call)
		{
			assert(sub->type);
			
			if (sub->type->kind != tk_lambda)
			{
				TODO;
				#if 0
				struct stringtree* tree = new_stringtree();
				
				stringtree_append_printf(tree,
					"%s: cannot make function call on '", argv0);
				
				{
					struct stringtree* subtree = type_print2(sub->type);
					stringtree_append_tree(tree, subtree);
					free_stringtree(subtree);
				}
				
				stringtree_append_printf(tree, "' type!\n");
				
				stringtree_stream(tree, stderr);
				
				exit(1);
				
				free_stringtree(tree);
				#endif
			}
			
			struct lambda_type* lambda_type = (void*) sub->type;
			
			if (lambda_type->parameters->n != zexpression->args.n)
			{
				TODO;
				#if 0
				struct stringtree* tree = new_stringtree();
				
				stringtree_append_printf(tree,
					"%s: incorrect number of arguments in call on '", argv0);
				
				{
					struct stringtree* subtree = type_print2(sub->type);
					stringtree_append_tree(tree, subtree);
					free_stringtree(subtree);
				}
				
				stringtree_append_printf(tree, "' type!\n");
				
				stringtree_stream(tree, stderr);
				
				exit(1);
				
				free_stringtree(tree);
				#endif
			}
			
			struct expression_list* arguments = new_expression_list();
			
			bool all_literals = (sub->kind == ek_literal);
			
			for (unsigned i = 0, n = zexpression->args.n; i < n; i++)
			{
				struct expression* arg = specialize_expression(tcache, scope, zexpression->args.data[i]);
				
				if (arg->kind != ek_literal)
					all_literals = false;
				
				if (lambda_type->parameters->data[i] != arg->type)
				{
					struct stringtree* tree = new_stringtree();
					
					stringtree_append_printf(tree,
						"%s: function call with incorrect types!\n", argv0);
					
					stringtree_append_printf(tree,
						"%s: function type: ", argv0);
					
					{
						struct stringtree* subtree = type_print2(sub->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					
					stringtree_append_printf(tree, "\n");
					
					stringtree_append_printf(tree,
						"%s: %uth argument type: ", argv0, i);
					
					{
						struct stringtree* subtree = type_print2(arg->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					
					stringtree_append_printf(tree, "\n");
					
					stringtree_stream(tree, stderr);
					
					free_stringtree(tree);
					
					exit(1);
				}
				
				expression_list_append(arguments, arg);
				
				free_expression(arg);
			}
			
			if (all_literals)
			{
				struct literal_expression* spef = (void*) sub;
				
				struct lambda_value* lambda = (void*) spef->value;
				
				struct value_list* valargs = new_value_list();
				
				for (unsigned i = 0, n = arguments->n; i < n; i++)
				{
					struct expression* element = arguments->data[i];
					
					assert(element->kind == ek_literal);
					
					struct literal_expression* le = (void*) element;
					
					value_list_append(valargs, le->value);
				}
				
				struct value* result = funccall_run(tcache, lambda, valargs);
				
				assert(lambda_type->rettype == result->type);
				
				retval = new_literal_expression(result);
				
				free_value_list(valargs);
				
				free_value(result);
			}
			else
			{
				retval = new_funccall_expression(lambda_type->rettype, sub, arguments);
			}
			
			free_expression_list(arguments);
		}
		else
		{
			TODO;
		}
		
		free_expression(sub);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}















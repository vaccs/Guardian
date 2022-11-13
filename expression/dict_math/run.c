
#include <assert.h>
#include <debug.h>

#include <value/dict/struct.h>
#include <value/dict/new.h>

#include <value/compare.h>

#include <pair/value/struct.h>

#include <list/value_pair/struct.h>
#include <list/value_pair/new.h>
#include <list/value_pair/append.h>
#include <list/value_pair/free.h>

#include "run.h"

struct value* dict_math_union_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right)
{
	ENTER;
	
	struct value_pair_list* leftlist = left->elements;
	struct value_pair_list* rightlist = right->elements;
	
	struct value_pair_list* unionlist = new_value_pair_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value_pair *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le->key, re->key);
		
		if (cmp < 0)
		{
			value_pair_list_append(unionlist, le), i++;
		}
		else if (cmp > 0)
		{
			value_pair_list_append(unionlist, re), j++;
		}
		else
		{
			value_pair_list_append(unionlist, re), i++, j++;
		}
	}
	
	while (i < n)
	{
		TODO;
	}
	
	while (j < m)
	{
		struct value_pair *re = rightlist->data[j];
		value_pair_list_append(unionlist, re), j++;
	}
	
	struct value* value = new_dict_value(type, unionlist);
	
	free_value_pair_list(unionlist);
	
	EXIT;
	return value;
}

struct value* dict_math_intersect_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right)
{
	ENTER;
	
	struct value_pair_list* leftlist = left->elements;
	struct value_pair_list* rightlist = right->elements;
	
	struct value_pair_list* unionlist = new_value_pair_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value_pair *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le->key, re->key);
		
		if (cmp < 0)
		{
			i++;
		}
		else if (cmp > 0)
		{
			j++;
		}
		else
		{
			value_pair_list_append(unionlist, re), i++, j++;
		}
	}
	
	struct value* value = new_dict_value(type, unionlist);
	
	free_value_pair_list(unionlist);
	
	EXIT;
	return value;
}


struct value* dict_math_symdifference_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right)
{
	ENTER;
	
	struct value_pair_list* leftlist = left->elements;
	struct value_pair_list* rightlist = right->elements;
	
	struct value_pair_list* unionlist = new_value_pair_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value_pair *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le->key, re->key);
		
		if (cmp < 0)
		{
			value_pair_list_append(unionlist, le), i++;
		}
		else if (cmp > 0)
		{
			value_pair_list_append(unionlist, re), j++;
		}
		else
		{
			i++, j++;
		}
	}
	
	while (i < n)
	{
		TODO;
	}
	
	while (j < m)
	{
		TODO;
	}
	
	struct value* value = new_dict_value(type, unionlist);
	
	free_value_pair_list(unionlist);
	
	EXIT;
	return value;
}

struct value* dict_math_difference_run(
	struct type* type,
	struct dict_value* left,
	struct dict_value* right)
{
	ENTER;
	
	struct value_pair_list* leftlist = left->elements;
	struct value_pair_list* rightlist = right->elements;
	
	struct value_pair_list* unionlist = new_value_pair_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value_pair *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le->key, re->key);
		
		if (cmp < 0)
		{
			value_pair_list_append(unionlist, le), i++;
		}
		else if (cmp > 0)
		{
			j++;
		}
		else
		{
			i++, j++;
		}
	}
	
	while (i < n)
	{
		TODO;
	}
	
	while (j < m)
	{
		TODO;
	}
	
	struct value* value = new_dict_value(type, unionlist);
	
	free_value_pair_list(unionlist);
	
	EXIT;
	return value;
}








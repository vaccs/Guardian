
#include <assert.h>
#include <debug.h>

#include <value/set/struct.h>
#include <value/set/new.h>

#include <value/compare.h>

#include <list/value/struct.h>
#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include "run.h"

struct value* set_math_union_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right)
{
	ENTER;
	
	struct value_list* leftlist = left->elements;
	struct value_list* rightlist = right->elements;
	
	struct value_list* unionlist = new_value_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le, re);
		
		if (cmp < 0)
		{
			value_list_append(unionlist, le), i++;
		}
		else if (cmp > 0)
		{
			value_list_append(unionlist, re), j++;
		}
		else
		{
			value_list_append(unionlist, re), i++, j++;
		}
	}
	
	while (i < n)
	{
		TODO;
	}
	
	while (j < m)
	{
		struct value *re = rightlist->data[j];
		value_list_append(unionlist, re), j++;
	}
	
	struct value* value = new_set_value(type, unionlist);
	
	free_value_list(unionlist);
	
	EXIT;
	return value;
}

struct value* set_math_intersect_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right)
{
	ENTER;
	
	struct value_list* leftlist = left->elements;
	struct value_list* rightlist = right->elements;
	
	struct value_list* unionlist = new_value_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le, re);
		
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
			value_list_append(unionlist, re), i++, j++;
		}
	}
	
	struct value* value = new_set_value(type, unionlist);
	
	free_value_list(unionlist);
	
	EXIT;
	return value;
}


struct value* set_math_symdifference_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right)
{
	ENTER;
	
	struct value_list* leftlist = left->elements;
	struct value_list* rightlist = right->elements;
	
	struct value_list* unionlist = new_value_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le, re);
		
		if (cmp < 0)
		{
			value_list_append(unionlist, le), i++;
		}
		else if (cmp > 0)
		{
			value_list_append(unionlist, re), j++;
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
	
	struct value* value = new_set_value(type, unionlist);
	
	free_value_list(unionlist);
	
	EXIT;
	return value;
}

struct value* set_math_difference_run(
	struct type* type,
	struct set_value* left,
	struct set_value* right)
{
	ENTER;
	
	struct value_list* leftlist = left->elements;
	struct value_list* rightlist = right->elements;
	
	struct value_list* unionlist = new_value_list();
	
	unsigned i = 0, n = leftlist->n, j = 0, m = rightlist->n;
	
	while (i < n && j < m)
	{
		struct value *le = leftlist->data[i], *re = rightlist->data[j];
		
		int cmp = compare_values(le, re);
		
		if (cmp < 0)
		{
			value_list_append(unionlist, le), i++;
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
	
	struct value* value = new_set_value(type, unionlist);
	
	free_value_list(unionlist);
	
	EXIT;
	return value;
}








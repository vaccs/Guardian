
#include <assert.h>

#include <debug.h>

/*#include <type/list/struct.h>*/

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <type/struct.h>
#include <type/dict/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_inc.h>
#include <out/function_queue/submit_compare.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_index_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct dict_index_expression* this = (void*) super;
	
	struct dict_type* dtype = (void*) this->dict->type;
	
/*	unsigned tid = super->type->id;*/
	
	stringtree_append_printf(tree, "({");
	
	struct stringtree* dict = expression_print_source(this->dict, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* dict = ", this->dict->type->id);
	stringtree_append_tree(tree, dict);
	stringtree_append_printf(tree, ";");
	
	struct stringtree* key = expression_print_source(this->index, shared, environment);
	stringtree_append_printf(tree, "struct type_%u* key = ", this->index->type->id);
	stringtree_append_tree(tree, key);
	stringtree_append_printf(tree, ";");
	
	stringtree_append_printf(tree, "	signed l = 0, r = dict->n - 1;");
	
	stringtree_append_printf(tree, "	struct type_%u* value = NULL;", dtype->value->id);
	
	stringtree_append_printf(tree, "	while (!value && r >= l)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		int mid = l + (r - l) / 2;");
	
	unsigned compare_id = function_queue_submit_compare(shared->fqueue, dtype->key);
	stringtree_append_printf(tree, "		int cmp = func_%u(dict->data[mid].key, key);", compare_id);
	
	stringtree_append_printf(tree, "		if (cmp > 0)");
	stringtree_append_printf(tree, "			r = mid - 1;");
	stringtree_append_printf(tree, "		else if (cmp < 0)");
	stringtree_append_printf(tree, "			l = mid + 1;");
	stringtree_append_printf(tree, "		else");
	
	unsigned inc_id = function_queue_submit_inc(shared->fqueue, dtype->value);
	stringtree_append_printf(tree, "			value = func_%u(dict->data[mid].value);", inc_id);
	stringtree_append_printf(tree, "	}");
	
	stringtree_append_printf(tree, "	if (!value)");
	stringtree_append_printf(tree, "	{");
	stringtree_append_printf(tree, "		assert(!\"TODO\");");
	stringtree_append_printf(tree, "	}");
	
	unsigned free_dict_id = function_queue_submit_free(shared->fqueue, this->dict->type);
	stringtree_append_printf(tree, "	func_%u(dict);", free_dict_id);
	
	unsigned free_key_id = function_queue_submit_free(shared->fqueue, this->index->type);
	stringtree_append_printf(tree, "	func_%u(key);", free_key_id);
	
	stringtree_append_printf(tree, "	value;");
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(dict), free_stringtree(key);
	
	EXIT;
	return tree;
}


















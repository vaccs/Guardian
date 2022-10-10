
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

/*#include <type/print_source.h>*/

#include <out/shared.h>
#include <out/type_lookup/lookup.h>
#include <out/function_lookup/lookup_new.h>
#include <out/function_lookup/lookup_compare.h>
#include <out/function_lookup/lookup_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

static const char* lookup[] = {
	[cek_equal_to] = "==",
};

struct stringtree* comparison_expression_print_source(
	struct expression* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct comparison_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	type_lookup(shared->tlookup, this->type, NULL);
	
	unsigned tid = this->type->id;
	
	struct stringtree* left = expression_print_source(this->left, shared);
	
	struct stringtree* right = expression_print_source(this->right, shared);
	
	stringtree_append_printf(tree, "type_%u *left = ", tid);
	stringtree_append_tree(tree, left);
	stringtree_append_printf(tree, ", *right = ");
	stringtree_append_tree(tree, right);
	stringtree_append_printf(tree, ";\n");
	
	type_lookup(shared->tlookup, super->type, NULL);
	
	unsigned rettype_id = super->type->id;
	unsigned new_id = function_lookup_new(shared->flookup, super->type);
	unsigned compare_id = function_lookup_compare(shared->flookup, this->type, 0);
	
	stringtree_append_printf(tree, ""
		"type_%u* cmp = func_%u(func_%u(left, right) %s 0);"
	"", rettype_id, new_id, compare_id, lookup[this->kind]);
	
	unsigned free_id = function_lookup_free(shared->flookup, this->type, 0);
	
	stringtree_append_printf(tree, "func_%u(left), func_%u(right);", free_id, free_id);
	
	stringtree_append_printf(tree, "cmp;", lookup[this->kind]);
	
	stringtree_append_printf(tree, "})");
	
	free_stringtree(left), free_stringtree(right);
	
	EXIT;
	return tree;
}















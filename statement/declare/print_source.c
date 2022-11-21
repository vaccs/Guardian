
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/print_source.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* declare_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct environment_type* environment_type)
{
	ENTER;
	
	assert(super->kind == sk_declare);
	
	struct stringtree* tree = new_stringtree();
	
	struct declare_statement* this = (void*) super;
	
	dpvs(this->name);

	struct string* name = this->name;

	stringtree_append_printf(tree, "environment->$%.*s = ", name->len, name->chars);

	struct stringtree* subtext =
		expression_print_source(this->expression, shared, environment_type);

	stringtree_append_tree(tree, subtext);

	stringtree_append_printf(tree, ";");

	free_stringtree(subtext);
	
	EXIT;
	return tree;
}













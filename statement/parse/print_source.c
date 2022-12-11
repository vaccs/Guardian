
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <type/struct.h>

#include <type_cache/get_grammar_type.h>

#include <out/shared.h>
#include <out/function_queue/submit_free.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* parse_statement_print_source(
	struct statement* super,
	struct out_shared* shared,
	struct type* environment_type)
{
	ENTER;
	
	assert(super->kind == sk_parse);
	
	struct parse_statement* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "{");
	
	if (this->expression)
	{
		stringtree_append_printf(tree, "struct type_%u* parseme = ", this->expression->type->id);
		
		struct stringtree* subtree = expression_print_source(this->expression, shared, environment_type);
		
		stringtree_append_tree(tree, subtree);
		
		stringtree_append_printf(tree, ";");
		
		stringtree_append_printf(tree, "unsigned n = parseme->len;");
		
		stringtree_append_printf(tree, "unsigned char* buffer = malloc(sizeof(*buffer) * (n + 1));");
		
		stringtree_append_printf(tree, "memcpy(buffer, parseme->chars, n);");
		
		stringtree_append_printf(tree, "buffer[n] = 0;");
		
		stringtree_append_printf(tree, "FILE* stream = fopen((char*) buffer, \"r\");");
		stringtree_append_printf(tree, "if (!stream)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: error when attemping to "
			"open '%%s' in %%%%parse directive on line %u!\\n\", argv0, (char*) buffer); ", this->line);
		stringtree_append_printf(tree, "	exit(1);");
		stringtree_append_printf(tree, "}");
		
		struct type* type = type_cache_get_grammar_type(shared->tcache, this->grammar_name);
		
		stringtree_append_printf(tree, "struct type_%u* start = parse(stream, %u, %u);", type->id, this->start_id, this->grammar_id);
		
		unsigned start_free_id = function_queue_submit_free(shared->fqueue, type);
		
		stringtree_append_printf(tree, "func_%u(start);", start_free_id);
		
		unsigned path_free_id = function_queue_submit_free(shared->fqueue, this->expression->type);
		
		stringtree_append_printf(tree, "func_%u(parseme);", path_free_id);
		
		stringtree_append_printf(tree, "fclose(stream);");
		
		stringtree_append_printf(tree, "free(buffer);");
		
		free_stringtree(subtree);
	}
	else
	{
		stringtree_append_printf(tree, "const char* path = *argv++;");
		
		stringtree_append_printf(tree, "if (!path)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	fprintf(stderr, \"\\e[1m%%s:\\e[m expected "
			"path to be given on the command line for the %%%%parse directive on line %u!\\n\", argv0);", this->line);
		stringtree_append_printf(tree, "	exit(1);");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "FILE* stream = fopen(path, \"r\");");
		
		stringtree_append_printf(tree, "if (!stream)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	fprintf(stderr, \"\\e[1m%%s:\\e[m error when attemping to "
			"open '%%s' in %%%%parse directive on line %u: %%m\\n\", argv0, path); ", this->line);
		stringtree_append_printf(tree, "	exit(1);");
		stringtree_append_printf(tree, "}\n");
		
		struct type* type = type_cache_get_grammar_type(shared->tcache, this->grammar_name);
		
		stringtree_append_printf(tree, "struct type_%u* start = parse(stream, %u, %u);", type->id, this->start_id, this->grammar_id);
		
		unsigned start_free_id = function_queue_submit_free(shared->fqueue, type);
		
		stringtree_append_printf(tree, "func_%u(start);", start_free_id);
		
		stringtree_append_printf(tree, "fclose(stream);");
	}
	
	stringtree_append_printf(tree, "}");
	
	EXIT;
	return tree;
}














#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_free.h>

#include <type/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* isexecutableby_form_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	struct isexecutableby_form_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	type_queue_submit(shared->tqueue, super->type);
	
	stringtree_append_printf(tree, "({");
	
	{
		stringtree_append_printf(tree, "struct type_%u* user = ", this->user->type->id);
		struct stringtree* subtree = expression_print_source(this->user, shared, environment);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
	}
	
	{
		stringtree_append_printf(tree, "struct type_%u* path = ", this->path->type->id);
		struct stringtree* subtree = expression_print_source(this->path, shared, environment);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
	}
	
	{
		stringtree_append_printf(tree, "unsigned char* native_user = malloc(user->n + 1);");
		stringtree_append_printf(tree, "unsigned char* native_path = malloc(path->n + 1);");
		
		stringtree_append_printf(tree, "for (unsigned i = 0; i < user->n; i++)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	native_user[i] = user->data[i]->value;");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "for (unsigned i = 0; i < path->n; i++)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	native_path[i] = path->data[i]->value;");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "native_user[user->n] = 0;");
		
		stringtree_append_printf(tree, "native_path[path->n] = 0;");
		
		stringtree_append_printf(tree, "bool error = false;");
		
		stringtree_append_printf(tree, "struct passwd* passwd;");
		stringtree_append_printf(tree, "pid_t child;");
		stringtree_append_printf(tree, "int wstatus;");
		
		stringtree_append_printf(tree, "if (!(passwd = getpwnam((char*) native_user)))");
		stringtree_append_printf(tree, "	error = true;");
		stringtree_append_printf(tree, "else if ((child = fork()) < 0)");
		stringtree_append_printf(tree, "	error = true;");
		stringtree_append_printf(tree, "else if (child) error = false");
		stringtree_append_printf(tree, "	|| waitpid(child, &wstatus, 0) < 0");
		stringtree_append_printf(tree, "	|| !WIFEXITED(wstatus)");
		stringtree_append_printf(tree, "	|| WEXITSTATUS(wstatus);");
		stringtree_append_printf(tree, "else exit(false");
		stringtree_append_printf(tree, "	|| setregid(passwd->pw_uid, passwd->pw_uid) < 0");
		stringtree_append_printf(tree, "	|| setreuid(passwd->pw_gid, passwd->pw_gid) < 0");
		stringtree_append_printf(tree, "	|| access((char*) native_path, R_OK | X_OK) < 0);");
		
		stringtree_append_printf(tree, "free(native_user);");
		
		stringtree_append_printf(tree, "free(native_path);");
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->user->type);
		stringtree_append_printf(tree, "func_%u(user);", free_id);
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->path->type);
		stringtree_append_printf(tree, "func_%u(path);", free_id);
	}
	
	{
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		stringtree_append_printf(tree, "func_%u(!error);", new_id);
	}
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}















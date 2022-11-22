
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
		stringtree_append_printf(tree, "unsigned char* native_user = malloc(user->n + 1);");
		
		stringtree_append_printf(tree, "for (unsigned i = 0; i < user->n; i++)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	native_user[i] = user->data[i]->value;");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "native_user[user->n] = 0;");
		
		stringtree_append_printf(tree, "struct passwd *entry = getpwnam((char*) native_user);");
		
		stringtree_append_printf(tree, "if (!entry)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: getpwnam('%%s'): %%m\\n\", argv0, native_user);");
		stringtree_append_printf(tree, "	exit(1);");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "printf(\"%%s: setegid(%%u)\\n\", argv0, entry->pw_gid);");
		
		stringtree_append_printf(tree, "if (setegid(entry->pw_gid) < 0)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: setegid(%%u): %%m\\n\", argv0, entry->pw_gid);");
		stringtree_append_printf(tree, "	exit(1);");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "printf(\"%%s: seteuid(%%u)\\n\", argv0, entry->pw_uid);");
		
		stringtree_append_printf(tree, "if (seteuid(entry->pw_uid) < 0)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: seteuid(%%u): %%m\\n\", argv0, entry->pw_uid);");
		stringtree_append_printf(tree, "	exit(1);");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "free(native_user);");
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->user->type);
		stringtree_append_printf(tree, "func_%u(user);", free_id);
	}
	
	{
		stringtree_append_printf(tree, "struct type_%u* path = ", this->path->type->id);
		struct stringtree* subtree = expression_print_source(this->path, shared, environment);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		free_stringtree(subtree);
	}
	
	{
		stringtree_append_printf(tree, "unsigned char* native_path = malloc(path->n + 1);");
		
		stringtree_append_printf(tree, "for (unsigned i = 0; i < path->n; i++)");
		stringtree_append_printf(tree, "{");
		stringtree_append_printf(tree, "	native_path[i] = path->data[i]->value;");
		stringtree_append_printf(tree, "}");
		
		stringtree_append_printf(tree, "native_path[path->n] = 0;");
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree, "printf(\"%%s: access(\\\"%%s\\\", X_OK)\\n\", argv0, native_path);");
		
		stringtree_append_printf(tree, ""
			"struct type_%u* result = func_%u(faccessat(AT_FDCWD, (char*) native_path, X_OK, AT_EACCESS) == 0);",
			super->type->id, new_id);
		
		stringtree_append_printf(tree, "free(native_path);");
	}
	
	{
		unsigned free_id = function_queue_submit_free(shared->fqueue, this->path->type);
		stringtree_append_printf(tree, "func_%u(path);", free_id);
	}
	
	stringtree_append_printf(tree, "printf(\"%%s: setegid(%%u)\\n\", argv0, 0);");
	
	stringtree_append_printf(tree, "if (seteuid(0) < 0)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: seteuid(%%u): %%m\\n\", argv0, 0);");
	stringtree_append_printf(tree, "	exit(1);");
	stringtree_append_printf(tree, "}");
	
		stringtree_append_printf(tree, "printf(\"%%s: seteuid(%%u)\\n\", argv0, 0);");
		
	stringtree_append_printf(tree, "if (setegid(0) < 0)");
	stringtree_append_printf(tree, "{");
	stringtree_append_printf(tree, "	fprintf(stderr, \"%%s: setegid(%%u): %%m\\n\", argv0, 0);");
	stringtree_append_printf(tree, "	exit(1);");
	stringtree_append_printf(tree, "}");
	
	stringtree_append_printf(tree, "result;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}















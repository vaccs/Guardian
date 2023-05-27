
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <debug.h>

#include <defines/argv0.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
/*#include <avl/search.h>*/
#include <avl/free_tree.h>

#include <misc/break_and_open_path.h>

#include <lex/add_EOF_token.h>

#ifdef VERBOSE
#include <misc/default_sighandler.h>
#endif

#include "process_skip.h"
#include "process_assert.h"
#include "process_print.h"
#include "process_parse.h"
#include "process_declare.h"
#include "process_grammar.h"

#include "parse.h"
#include "driver.h"

struct file_info
{
	dev_t st_dev;
	ino_t st_ino;
};

static struct file_info* new_file_info(dev_t st_dev, ino_t st_ino)
{
	ENTER;
	
	struct file_info* this = smalloc(sizeof(*this));
	
	this->st_dev = st_dev;
	this->st_ino = st_ino;
	
	EXIT;
	return this;
}

static int compare(const void* a, const void* b)
{
	const struct file_info *A = a, *B = b;
	if (A->st_dev > B->st_dev)
		return +1;
	if (A->st_dev < B->st_dev)
		return -1;
	if (A->st_ino > B->st_ino)
		return +1;
	if (A->st_ino < B->st_ino)
		return -1;
	return +0;
}

void parse_driver(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct raw_statement_list* statements,
	const char* input_path)
{
	ENTER;
	
	dpvs(input_path);
	
	#ifdef VERBOSE
	void handler1(int _)
	{
		char buffer[1000] = {};
		
		size_t len = snprintf(buffer, sizeof(buffer),
			"\e[K" "guardian: parsing '%s' ...\r", input_path);
		
		if (write(1, buffer, len) != len)
		{
			abort();
		}
	}
	
	signal(SIGALRM, handler1);
	#endif
	
	struct avl_tree_t* seen = avl_alloc_tree(compare, free);
	
	void helper(int dirfd, const char* path)
	{
		struct stat statbuf;
		ENTER;
		
		struct br_rettype brt = break_and_open_path(dirfd, path);
		
		if (fstat(brt.fd, &statbuf) < 0)
		{
			TODO;
			exit(1);
		}
		
		struct file_info* finfo = new_file_info(statbuf.st_dev, statbuf.st_ino);
		
		if (avl_insert(seen, finfo))
		{
			FILE* stream = fdopen(brt.fd, "r");
			
			if (!stream)
			{
				TODO;
				exit(1);
			}
			
			struct zebu_$start* start = zebu_parse(stream);
			
			for (unsigned i = 0, n = start->statements.n; i < n; i++)
			{
				struct zebu_statement* statement = start->statements.data[i];
				
				if (statement->include)
				{
					char* path = (void*) statement->include->path->data;
					
					path++, path[strlen(path) - 1] = 0;
					
					helper(brt.dirfd, path);
				}
				else  if (statement->skip)
				{
					process_skip(lex, statement->skip);
				}
				else if (statement->assert)
				{
					process_assert(statements, statement->assert);
				}
				else if (statement->print)
				{
					process_print(statements, statement->print);
				}
				else if (statement->parse)
				{
					process_parse(lex, grammar, types, statements, statement->parse);
				}
				else if (statement->declare)
				{
					process_declare(statements, statement->declare);
				}
				else if (statement->grammar)
				{
					process_grammar(lex, grammar, types, statement->grammar);
				}
				else
				{
					TODO;
				}
			}
			
			free_zebu_$start(start);
			
			fclose(stream);
		}
		else if (errno == EEXIST)
		{
			free(finfo);
		}
		else
		{
			TODO;
			exit(1);
		}
		
		close(brt.fd);
		
		if (dirfd != brt.dirfd && brt.dirfd > 0)
			close(brt.dirfd);
		
		EXIT;
	}
	
	helper(AT_FDCWD, input_path);
	
	#ifdef VERBOSE
	signal(SIGALRM, default_sighandler);
	#endif
	
	lex_add_EOF_token(lex);
	
	avl_free_tree(seen);
	
	EXIT;
}



















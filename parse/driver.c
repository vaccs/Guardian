
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <debug.h>

#include <defines/argv0.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/search.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

#include <misc/break_and_open_path.h>

#include <lex/add_EOF_token.h>

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
	int fd;
	
	dev_t st_dev;
	ino_t st_ino;
};

static struct file_info* new_file_info(int fd)
{
	ENTER;
	
	struct file_info* this = smalloc(sizeof(*this));
	
	dpv(fd);
	
	struct stat statbuf;
	
	if (fstat(fd, &statbuf) < 0)
	{
		TODO;
		exit(1);
	}
	
	this->fd = fd;
	
	this->st_dev = statbuf.st_dev;
	this->st_ino = statbuf.st_ino;
	
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

static void free_file_info(void* ptr)
{
	struct file_info* this = ptr;
	
	free(this);
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
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* queued = avl_alloc_tree(compare, free_file_info);
	
	// setup:
	{
		int fd = open(input_path, O_RDONLY);
		
		if (fd < 0)
		{
			fprintf(stderr, "%s: cannot open input file '%s': %m!\n", argv0, input_path);
			exit(1);
		}
		
		struct file_info* info = new_file_info(fd);
		
		avl_insert(queued, info);
		
		quack_append(todo, info);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct file_info* info = quack_pop(todo);
		
		dpv(info->fd);
		
		FILE* stream = fdopen(info->fd, "r");
		
		struct zebu_$start* start = zebu_parse(stream);
		
		for (unsigned i = 0, n = start->statements.n; i < n; i++)
		{
			struct zebu_statement* statement = start->statements.data[i];
			
			if (statement->using)
			{
				char* path = (void*) statement->using->path->data;
				
				dpvs(path);
				
				memmove(path, path + 1, strlen(path) - 1);
				path[strlen(path) - 2] = 0;
				
				dpvs(path);
				
				int fd = open(path, O_RDONLY);
				
				if (fd < 0)
				{
					fprintf(stderr, "%s: cannot open %%using-ed file '%s': %m!\n", argv0, path);
					exit(1);
				}
				
				struct file_info* info = new_file_info(fd);
				
				if (errno = 0, avl_insert(queued, info))
				{
					quack_append(todo, info);
				}
				else if (errno = EEXIST)
				{
					free_file_info(info);
				}
				else
				{
					TODO;
					exit(1);
				}
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
	
	lex_add_EOF_token(lex);
	
	avl_free_tree(queued);
	
	free_quack(todo);
	
	EXIT;
}



















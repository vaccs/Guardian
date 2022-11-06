
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>
#include <avl/free_tree.h>

#include <quack/new.h>
#include <quack/append.h>
#include <quack/pop.h>
#include <quack/is_nonempty.h>
#include <quack/free.h>

#include <misc/break_and_open_path.h>

#include <lex/add_EOF_token.h>

#include "skip.h"
#include "start.h"
#include "parse.h"
#include "driver.h"
#include "grammar.h"
#include "declare.h"
#include "assertion.h"

struct file_descriptor
{
	int fd;
	unsigned refcount;
};

static struct file_descriptor* new_file_descriptor(int fd)
{
	ENTER;
	
	dpv(fd);
	
	struct file_descriptor* this = smalloc(sizeof(*this));
	
	this->fd = fd;
	this->refcount = 1;
	
	EXIT;
	return this;
}

static struct file_descriptor* inc_file_descriptor(struct file_descriptor* this)
{
	this->refcount++;
	return this;
}

static void free_file_descriptor(struct file_descriptor* this)
{
	ENTER;
	
	if (!--this->refcount)
	{
		if (this->fd > 0)
			close(this->fd);
		free(this);
	}
	else
	{
		dpv(this->refcount);
	}
	
	EXIT;
}

struct file_info
{
	int fd;
	
	dev_t st_dev;
	ino_t st_ino;
	
	struct file_descriptor *abs_dirfd, *rel_dirfd;
};

static struct file_info* new_file_info(
	int fd,
	struct file_descriptor *abs_dirfd,
	struct file_descriptor *rel_dirfd)
{
	ENTER;
	
	struct file_info* this = smalloc(sizeof(*this));
	
	dpv(fd);
	
	this->fd = fd;
	
	this->abs_dirfd = inc_file_descriptor(abs_dirfd);
	this->rel_dirfd = inc_file_descriptor(rel_dirfd);
	
	EXIT;
	return this;
}

static int compare(const void* a, const void* b)
{
	TODO;
}

void parse_driver(
	struct lex* lex,
	struct avl_tree_t* grammar,
	struct avl_tree_t* types,
	struct avl_tree_t* declares,
	struct raw_assertion_list* assertions,
	struct type_cache* tcache,
	const char* input_path)
{
	ENTER;
	
	dpvs(input_path);
	
	struct quack* todo = new_quack();
	
	struct avl_tree_t* queued = avl_alloc_tree(compare, free);
	
	// setup:
	{
		struct br_rettype bun = break_and_open_path(AT_FDCWD, input_path);
		
		struct file_descriptor* des = new_file_descriptor(bun.dirfd);
		
		struct file_info* info = new_file_info(bun.fd, des, des);
		
		avl_insert(queued, info);
		
		quack_append(todo, info);
		
		free_file_descriptor(des);
	}
	
	while (quack_is_nonempty(todo))
	{
		struct file_info* info = quack_pop(todo);
		
		dpv(info->fd);
		
		FILE* stream = fdopen(info->fd, "r");
		
		struct zebu_$start* start = zebu_parse(stream);
		
		for (unsigned i = 0, n = start->usings.n; i < n; i++)
		{
			TODO;
		}
		
		for (unsigned i = 0, n = start->skips.n; i < n; i++)
		{
			process_skip(lex,  start->skips.data[i]);
		}
		
		for (unsigned i = 0, n = start->starts.n; i < n; i++)
		{
			process_start(lex, grammar, types, start->starts.data[i]);
		}
		
		for (unsigned i = 0, n = start->grammars.n; i < n; i++)
		{
			process_grammar(lex, grammar, types, declares, start->grammars.data[i]);
		}
		
		for (unsigned i = 0, n = start->declares.n; i < n; i++)
		{
			process_declare(grammar, declares, start->declares.data[i]);
		}
		
		for (unsigned i = 0, n = start->assertions.n; i < n; i++)
		{
			process_assertion(assertions, start->assertions.data[i]);
		}
		
		free_zebu_$start(start);
		
		fclose(stream);
		
		free_file_descriptor(info->abs_dirfd);
		free_file_descriptor(info->rel_dirfd);
	}
	
	lex_add_EOF_token(lex);
	
	avl_free_tree(queued);
	
	free_quack(todo);
	
	EXIT;
}



















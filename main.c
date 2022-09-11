
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "cmdln/process.h"
#include "cmdln/free.h"

int main(int argc, char* const* argv)
{
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	puts("Hello, World!");
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}


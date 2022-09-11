
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "cmdln/flags.h"
#include "cmdln/process.h"
#include "cmdln/free.h"

#include "parse/mains.h"

int main(int argc, char* const* argv)
{
	ENTER;
	
	struct cmdln* flags = cmdln_process(argc, argv);
	
	mains_parse(flags->input_path);
	
	puts("Hello, World!");
	
	free_cmdln(flags);
	
	EXIT;
	return 0;
}


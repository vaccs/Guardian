
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "usage.h"
#include "flags.h"
#include "process.h"
#include "minimize_lexer.h"

struct cmdln* cmdln_process(int argc, char* const* argv)
{
	ENTER;
	
	const char* input_path = NULL;
	bool verbose = false;
	
	int opt;
	while ((opt = getopt(argc, argv, "hvmi:")) != -1)
	{
		switch (opt)
		{
			case 'i':
				input_path = optarg;
				break;
			
			case 'v':
				verbose = true;
				break;
			
			case 'm':
				minimize_lexer = true;
				break;
			
			case 'h':
				usage(0);
				break;
			
			default:
				usage(1);
				break;
		}
	}
	
	if (!input_path)
		usage(1);
	
	struct cmdln* flags = smalloc(sizeof(*flags));
	
	flags->input_path = input_path;
	flags->verbose = verbose;
	
	dpvs(flags->input_path);
	dpvb(flags->verbose);
	
	EXIT;
	return flags;
}













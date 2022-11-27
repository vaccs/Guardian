
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "verbose.h"
#include "usage.h"
#include "flags.h"
#include "process.h"

struct cmdln* cmdln_process(int argc, char* const* argv)
{
	ENTER;
	
	const char* input_path = NULL;
	const char* output_path = NULL;
	
	bool minimize_lexer = false;
	
	int opt;
	while ((opt = getopt(argc, argv, "hvmi:o:")) != -1)
	{
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
				
			case 'v':
				#ifdef VERBOSE
				verbose = true;
				#endif
				break;
			
			case 'm':
				minimize_lexer = true;
				break;
			
			case 'i':
				input_path = optarg;
				break;
			
			case 'o':
				output_path = optarg;
				break;
			
			default:
				usage(1);
				break;
		}
	}
	
	if (!input_path || !output_path)
	{
		usage(1);
	}
	
	struct cmdln* flags = smalloc(sizeof(*flags));
	
	flags->input_path = input_path;
	flags->output_path = output_path;
	flags->minimize_lexer = minimize_lexer;
	
	dpvs(flags->input_path);
	dpvs(flags->output_path);
	dpvb(flags->minimize_lexer);
	
	#ifdef VERBOSE
	dpvb(verbose);
	#endif
	
	EXIT;
	return flags;
}













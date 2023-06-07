
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <getopt.h>

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
	
	#if (defined DEBUGGING) || (defined TESTING)
	bool print_shortest_accepting = false;
	#endif
	
	int opt, option_index;
	const struct option long_options[] = {
		{"input",                  required_argument, 0, 'i'},
		{"output",                       no_argument, 0, 'o'},
		{"minimize-lexer",               no_argument, 0, 'm'},
		{"verbose",                      no_argument, 0, 'v'},
		{"help",                         no_argument, 0, 'h'},
		#if (defined DEBUGGING) || (defined TESTING)
		{"print-shortest-accepting",     no_argument, 0,  0 },
		#endif
		{ 0,                                       0, 0,  0 },
	};
	
	HERE;
	
	while ((opt = getopt_long(argc, argv,
		"i:"
		"o:"
		"m"
		"v"
		"h",
		long_options, &option_index)) >= 0)
	{
		switch (opt ?: option_index)
		{
			case 'i':
				input_path = optarg;
				break;
			
			case 'v':
				#ifdef VERBOSE
				verbose = true;
				#endif
				break;
			
			case 'm':
				minimize_lexer = true;
				break;
			
			case 'o':
				output_path = optarg;
				break;
			
			case 'h':
				usage(0);
				break;
			
			#if (defined DEBUGGING) || (defined TESTING)
			case 5:
			  print_shortest_accepting = true;
			  break;
			#endif
			
			default:
				usage(1);
				break;
		}
	}
	
	#if (defined DEBUGGING) || (defined TESTING)
	if (!input_path || (!print_shortest_accepting && !output_path))
	#else
	if (!input_path || !output_path)
	#endif
	{
		usage(1);
	}
	
	struct cmdln* flags = smalloc(sizeof(*flags));
	
	flags->input_path = input_path;
	flags->output_path = output_path;
	flags->minimize_lexer = minimize_lexer;
	#if (defined DEBUGGING) || (defined TESTING)
	flags->print_shortest_accepting = print_shortest_accepting;
	#endif
	
	dpvs(flags->input_path);
	dpvs(flags->output_path);
	dpvb(flags->minimize_lexer);
	#if (defined DEBUGGING) || (defined TESTING)
	dpvb(flags->print_shortest_accepting);
	#endif
	
	#ifdef VERBOSE
	dpvb(verbose);
	#endif
	
	EXIT;
	return flags;
}













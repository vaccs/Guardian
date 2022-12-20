
#include <stdio.h>
#include <stdlib.h>

#include <defines/argv0.h>

#include "usage.h"

void usage(int code)
{
	printf("usage: %s [-hmv] -i /path/to/input.guard -o /path/to/outout.c\n", argv0);
	
	printf("-i <path>\n");
	printf("	Gives Guardian the path to the initial file containing the\n");
	printf("	file specification for Guardian to generate a checker for.\n");
	printf("	If the file specification spans multiple files the additional\n");
	printf("	files would need to be directly or indirectly %%include-d\n");
	printf("	by the initial file.\n");
	printf("\n");
	
	printf("-o <path>\n");
	printf("	Gives Guardian the path to where to write the generated source\n");
	printf("	code to. After Guardian is complete, the generated souce code\n");
	printf("	would have to be compiled into an executable as a seperate step.\n");
	printf("	Remember to link that executable with '-lgmp' and '-lm'!\n");
	printf("\n");
	
	printf("-m\n");
	printf("	Tells Guardian to \"minimize\" the generated tokenizer. The\n");
	printf("	particular appoarch Guardian uses to generate its tokenizer's\n");
	printf("	state machine can sometimes yield very large transition tables.\n");
	printf("	This flag tells Guardian to run another pass over the generated\n");
	printf("	state machine merging states that it can prove to be redundant\n");
	printf("	or unneeded. The result is a state machine that functions the\n");
	printf("	same way, but has the fewest number of transitions and states.\n");
	printf("	This additional pass can sometimes take a long time, so it is\n");
	printf("	disabled by default.\n");
	printf("\n");
	
	printf("-v\n");
	printf("	Tells Guardian to be more \textit{verbose} about the work that it\n");
	printf("	is doing to convert the file specification read from the input\n");
	printf("	file(s) to C source code.\n");
	printf("\n");
	
	printf("-h\n");
	printf("	Tells Guardian to print out a usage message similar to the\n");
	printf("	content in this section.\n");
	
	exit(code);
}


















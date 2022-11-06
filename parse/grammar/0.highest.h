
#include <gegex/gbundle.h>

struct zebu_grammar_highest;
struct lex;

struct gbundle read_grammar_highest(
	struct lex* lex,
	struct zebu_grammar_highest* highest);

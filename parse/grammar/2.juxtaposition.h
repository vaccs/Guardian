
#include <gegex/gbundle.h>

struct zebu_grammar_juxtaposition;
struct lex;

struct gbundle read_grammar_juxtaposition(
	struct lex* lex,
	struct zebu_grammar_juxtaposition* juxtaposition);

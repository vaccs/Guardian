
#include <gegex/gbundle.h>

struct zebu_grammar;
struct lex;

struct gbundle read_grammar_root(
	struct lex* lex,
	struct zebu_grammar* grammar);


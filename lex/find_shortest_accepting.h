
struct lex_state;
struct unsignedset;

unsigned char* lex_find_shortest_accepting(
	struct lex_state* source,
	struct unsignedset* acceptme);

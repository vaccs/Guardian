
struct structinfo;
struct string;

void gegex_add_grammar_transition(
	struct gegex* this,
	struct string* grammar,
	struct structinfo* structinfo,
	struct gegex* to);


struct zpexpressionset;
struct zebu_primary_expression;

void zpexpressionset_foreach(
	const struct zpexpressionset* this,
	void (*runme)(struct zebu_primary_expression* zpexpression));




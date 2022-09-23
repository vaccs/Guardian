
#include <stdio.h>

struct token
{
	unsigned char* data;
	unsigned len, refcount;
};

struct zebu_$start
{
	struct zebu_root* root;
	unsigned refcount;
};

struct zebu_additive_expression
{
	unsigned refcount;
};

struct zebu_and_expression
{
	unsigned refcount;
};

struct zebu_charset
{
	struct zebu_charset_symdiff* base;
	struct {
		struct zebu_charset_symdiff** data;
		unsigned n, cap;
	} ors;
	unsigned refcount;
};

struct zebu_charset_highest
{
	struct token* character;
	struct token* integer;
	struct zebu_charset* subcharset;
	unsigned refcount;
};

struct zebu_charset_intersect
{
	struct zebu_charset_range* base;
	struct {
		struct zebu_charset_range** data;
		unsigned n, cap;
	} intersects;
	unsigned refcount;
};

struct zebu_charset_prefix
{
	struct zebu_charset_highest* base;
	struct token* emark;
	unsigned refcount;
};

struct zebu_charset_range
{
	struct zebu_charset_prefix* left;
	struct zebu_charset_prefix* right;
	unsigned refcount;
};

struct zebu_charset_symdiff
{
	struct zebu_charset_intersect* base;
	struct {
		struct zebu_charset_intersect** data;
		unsigned n, cap;
	} xors;
	unsigned refcount;
};

struct zebu_conditional_expression
{
	unsigned refcount;
};

struct zebu_entry
{
	struct zebu_expression* assertion;
	struct token* debug;
	struct token* error;
	struct zebu_expression* expression;
	struct zebu_grammar* grammar;
	struct token* name;
	struct token* note;
	struct token* path;
	struct zebu_regex* regex;
	struct token* skip;
	struct token* start;
	struct token* using;
	struct token* warning;
	unsigned refcount;
};

struct zebu_equality_expression
{
	unsigned refcount;
};

struct zebu_exclusive_or_expression
{
	unsigned refcount;
};

struct zebu_exponentiation_expression
{
	unsigned refcount;
};

struct zebu_expression
{
	unsigned refcount;
};

struct zebu_grammar
{
	struct zebu_grammar_juxtaposition* base;
	struct {
		struct zebu_grammar_juxtaposition** data;
		unsigned n, cap;
	} ors;
	unsigned refcount;
};

struct zebu_grammar_highest
{
	struct token* character;
	struct zebu_charset* charset;
	struct token* integer;
	struct token* name;
	struct zebu_regex* regex;
	struct token* string;
	struct zebu_grammar* subgrammar;
	struct {
		struct token** data;
		unsigned n, cap;
	} tags;
	unsigned refcount;
};

struct zebu_grammar_juxtaposition
{
	struct zebu_grammar_postfix* base;
	struct {
		struct zebu_grammar_postfix** data;
		unsigned n, cap;
	} juxtapositions;
	unsigned refcount;
};

struct zebu_grammar_postfix
{
	struct zebu_grammar_highest* base;
	struct token* plus;
	struct token* qmark;
	struct token* star;
	unsigned refcount;
};

struct zebu_implication_expression
{
	unsigned refcount;
};

struct zebu_inclusive_or_expression
{
	unsigned refcount;
};

struct zebu_lambda_expression
{
	unsigned refcount;
};

struct zebu_logical_and_expression
{
	unsigned refcount;
};

struct zebu_logical_or_expression
{
	unsigned refcount;
};

struct zebu_multiplicative_expression
{
	unsigned refcount;
};

struct zebu_possession_expression
{
	unsigned refcount;
};

struct zebu_postfix_expression
{
	unsigned refcount;
};

struct zebu_primary_expression
{
	unsigned refcount;
};

struct zebu_primary_type
{
	unsigned refcount;
};

struct zebu_regex
{
	struct zebu_regex_juxtaposition* base;
	struct {
		struct zebu_regex_juxtaposition** data;
		unsigned n, cap;
	} ors;
	unsigned refcount;
};

struct zebu_regex_highest
{
	struct token* character;
	struct zebu_charset* charset;
	struct token* integer;
	struct token* string;
	struct zebu_regex* subregex;
	unsigned refcount;
};

struct zebu_regex_juxtaposition
{
	struct zebu_regex_postfix* base;
	struct {
		struct zebu_regex_postfix** data;
		unsigned n, cap;
	} juxtapositions;
	unsigned refcount;
};

struct zebu_regex_postfix
{
	struct zebu_regex_highest* base;
	struct token* plus;
	struct token* qmark;
	struct token* star;
	unsigned refcount;
};

struct zebu_relational_expression
{
	unsigned refcount;
};

struct zebu_root
{
	struct {
		struct zebu_entry** data;
		unsigned n, cap;
	} entries;
	unsigned refcount;
};

struct zebu_shift_expression
{
	unsigned refcount;
};

struct zebu_type
{
	unsigned refcount;
};

struct zebu_unary_expression
{
	unsigned refcount;
};



extern struct token* inc_token(struct token* this);
extern struct zebu_$start* inc_zebu_$start(struct zebu_$start* ptree);
extern struct zebu_additive_expression* inc_zebu_additive_expression(struct zebu_additive_expression* ptree);
extern struct zebu_and_expression* inc_zebu_and_expression(struct zebu_and_expression* ptree);
extern struct zebu_charset* inc_zebu_charset(struct zebu_charset* ptree);
extern struct zebu_charset_highest* inc_zebu_charset_highest(struct zebu_charset_highest* ptree);
extern struct zebu_charset_intersect* inc_zebu_charset_intersect(struct zebu_charset_intersect* ptree);
extern struct zebu_charset_prefix* inc_zebu_charset_prefix(struct zebu_charset_prefix* ptree);
extern struct zebu_charset_range* inc_zebu_charset_range(struct zebu_charset_range* ptree);
extern struct zebu_charset_symdiff* inc_zebu_charset_symdiff(struct zebu_charset_symdiff* ptree);
extern struct zebu_conditional_expression* inc_zebu_conditional_expression(struct zebu_conditional_expression* ptree);
extern struct zebu_entry* inc_zebu_entry(struct zebu_entry* ptree);
extern struct zebu_equality_expression* inc_zebu_equality_expression(struct zebu_equality_expression* ptree);
extern struct zebu_exclusive_or_expression* inc_zebu_exclusive_or_expression(struct zebu_exclusive_or_expression* ptree);
extern struct zebu_exponentiation_expression* inc_zebu_exponentiation_expression(struct zebu_exponentiation_expression* ptree);
extern struct zebu_expression* inc_zebu_expression(struct zebu_expression* ptree);
extern struct zebu_grammar* inc_zebu_grammar(struct zebu_grammar* ptree);
extern struct zebu_grammar_highest* inc_zebu_grammar_highest(struct zebu_grammar_highest* ptree);
extern struct zebu_grammar_juxtaposition* inc_zebu_grammar_juxtaposition(struct zebu_grammar_juxtaposition* ptree);
extern struct zebu_grammar_postfix* inc_zebu_grammar_postfix(struct zebu_grammar_postfix* ptree);
extern struct zebu_implication_expression* inc_zebu_implication_expression(struct zebu_implication_expression* ptree);
extern struct zebu_inclusive_or_expression* inc_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);
extern struct zebu_lambda_expression* inc_zebu_lambda_expression(struct zebu_lambda_expression* ptree);
extern struct zebu_logical_and_expression* inc_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);
extern struct zebu_logical_or_expression* inc_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);
extern struct zebu_multiplicative_expression* inc_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);
extern struct zebu_possession_expression* inc_zebu_possession_expression(struct zebu_possession_expression* ptree);
extern struct zebu_postfix_expression* inc_zebu_postfix_expression(struct zebu_postfix_expression* ptree);
extern struct zebu_primary_expression* inc_zebu_primary_expression(struct zebu_primary_expression* ptree);
extern struct zebu_primary_type* inc_zebu_primary_type(struct zebu_primary_type* ptree);
extern struct zebu_regex* inc_zebu_regex(struct zebu_regex* ptree);
extern struct zebu_regex_highest* inc_zebu_regex_highest(struct zebu_regex_highest* ptree);
extern struct zebu_regex_juxtaposition* inc_zebu_regex_juxtaposition(struct zebu_regex_juxtaposition* ptree);
extern struct zebu_regex_postfix* inc_zebu_regex_postfix(struct zebu_regex_postfix* ptree);
extern struct zebu_relational_expression* inc_zebu_relational_expression(struct zebu_relational_expression* ptree);
extern struct zebu_root* inc_zebu_root(struct zebu_root* ptree);
extern struct zebu_shift_expression* inc_zebu_shift_expression(struct zebu_shift_expression* ptree);
extern struct zebu_type* inc_zebu_type(struct zebu_type* ptree);
extern struct zebu_unary_expression* inc_zebu_unary_expression(struct zebu_unary_expression* ptree);


extern void free_token(struct token* this);
extern void free_zebu_$start(struct zebu_$start* ptree);

extern void free_zebu_additive_expression(struct zebu_additive_expression* ptree);

extern void free_zebu_and_expression(struct zebu_and_expression* ptree);

extern void free_zebu_charset(struct zebu_charset* ptree);

extern void free_zebu_charset_highest(struct zebu_charset_highest* ptree);

extern void free_zebu_charset_intersect(struct zebu_charset_intersect* ptree);

extern void free_zebu_charset_prefix(struct zebu_charset_prefix* ptree);

extern void free_zebu_charset_range(struct zebu_charset_range* ptree);

extern void free_zebu_charset_symdiff(struct zebu_charset_symdiff* ptree);

extern void free_zebu_conditional_expression(struct zebu_conditional_expression* ptree);

extern void free_zebu_entry(struct zebu_entry* ptree);

extern void free_zebu_equality_expression(struct zebu_equality_expression* ptree);

extern void free_zebu_exclusive_or_expression(struct zebu_exclusive_or_expression* ptree);

extern void free_zebu_exponentiation_expression(struct zebu_exponentiation_expression* ptree);

extern void free_zebu_expression(struct zebu_expression* ptree);

extern void free_zebu_grammar(struct zebu_grammar* ptree);

extern void free_zebu_grammar_highest(struct zebu_grammar_highest* ptree);

extern void free_zebu_grammar_juxtaposition(struct zebu_grammar_juxtaposition* ptree);

extern void free_zebu_grammar_postfix(struct zebu_grammar_postfix* ptree);

extern void free_zebu_implication_expression(struct zebu_implication_expression* ptree);

extern void free_zebu_inclusive_or_expression(struct zebu_inclusive_or_expression* ptree);

extern void free_zebu_lambda_expression(struct zebu_lambda_expression* ptree);

extern void free_zebu_logical_and_expression(struct zebu_logical_and_expression* ptree);

extern void free_zebu_logical_or_expression(struct zebu_logical_or_expression* ptree);

extern void free_zebu_multiplicative_expression(struct zebu_multiplicative_expression* ptree);

extern void free_zebu_possession_expression(struct zebu_possession_expression* ptree);

extern void free_zebu_postfix_expression(struct zebu_postfix_expression* ptree);

extern void free_zebu_primary_expression(struct zebu_primary_expression* ptree);

extern void free_zebu_primary_type(struct zebu_primary_type* ptree);

extern void free_zebu_regex(struct zebu_regex* ptree);

extern void free_zebu_regex_highest(struct zebu_regex_highest* ptree);

extern void free_zebu_regex_juxtaposition(struct zebu_regex_juxtaposition* ptree);

extern void free_zebu_regex_postfix(struct zebu_regex_postfix* ptree);

extern void free_zebu_relational_expression(struct zebu_relational_expression* ptree);

extern void free_zebu_root(struct zebu_root* ptree);

extern void free_zebu_shift_expression(struct zebu_shift_expression* ptree);

extern void free_zebu_type(struct zebu_type* ptree);

extern void free_zebu_unary_expression(struct zebu_unary_expression* ptree);



struct zebu_$start* zebu_parse(FILE* stream);

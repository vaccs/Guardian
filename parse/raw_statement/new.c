
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include <parse/parse.h>

#include "struct.h"
#include "new.h"

struct raw_statement* new_raw_assertion(
	unsigned line,
	enum assertion_kind kind,
	struct zebu_expression* expression)
{
	ENTER;
	
	struct raw_statement* this = smalloc(sizeof(*this));
	
	this->kind = rsk_assertion;
	
	this->assertion_kind = kind;
	
	this->expression = inc_zebu_expression(expression);
	
	this->refcount = 1;
	
	this->line = line;
	
	EXIT;
	return this;
}

struct raw_statement* new_raw_declaration(
	unsigned line,
	struct string* name,
	struct zebu_expression* expression)
{
	ENTER;
	
	struct raw_statement* this = smalloc(sizeof(*this));
	
	this->line = line;
	
	this->kind = rsk_declaration;
	
	this->name = inc_string(name);
	
	this->expression = inc_zebu_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}


struct raw_statement* new_raw_print(
	unsigned line,
	struct zebu_expression* expression)
{
	ENTER;
	
	struct raw_statement* this = smalloc(sizeof(*this));
	
	this->line = line;
	
	this->kind = rsk_print;
	
	this->expression = inc_zebu_expression(expression);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

struct raw_statement* new_raw_parse(
	unsigned line,
	struct zebu_expression* expression,
	struct string* grammar_name,
	struct gegex* grammar)
{
	ENTER;
	
	struct raw_statement* this = smalloc(sizeof(*this));
	
	this->kind = rsk_parse;
	
	this->line = line;
	
	this->expression = inc_zebu_expression(expression);
	
	this->name = inc_string(grammar_name);
	
	this->grammar = grammar;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}



















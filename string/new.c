
#if 0
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


#include <memory/smalloc.h>

#include <parse/tokenizer/struct.h>
#endif

#include <debug.h>

#include <parse/parse.h>

#include "struct.h"
#include "new.h"

struct string* new_string_from_token(const struct zebu_token* token)
{
	ENTER;
	
	dpvsn(token->data, token->len);
	
	struct string* this = smalloc(sizeof(*this));
	
	this->chars = memcpy(malloc(token->len), token->data, token->len);
	this->len = token->len;
	this->refcount = 1;
	
	EXIT;
	return this;
}

struct string* new_string(const char* str, unsigned len)
{
	ENTER;
	
	dpvsn(str, len);
	
	struct string* this = smalloc(sizeof(*this));
	
	this->chars = memcpy(malloc(len), str, len);
	this->len = len;
	this->refcount = 1;
	
	EXIT;
	return this;
}

#if 0
struct string* new_string_from_tokenchars(struct tokenizer* tokenizer)
{
	return new_string((const char*) tokenizer->tokenchars.chars);
}

struct string* new_string_from_format(const char* fmt, ...)
{
	ENTER;
	
	va_list ap;
	
	va_start(ap, fmt);
	
	char* chars;
	
	if (vasprintf(&chars, fmt, ap) < 0)
		abort();
	
	dpvs(chars);
	
	struct string* this = new_string_without_copy(chars);
	
	va_end(ap);
	
	EXIT;
	return this;
}
































#endif

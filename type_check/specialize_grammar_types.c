
#include <assert.h>

#include <debug.h>

#include <avl/foreach.h>
#include <avl/insert.h>

#include <named/structinfo/struct.h>
#include <named/type/new.h>

#include <parse/parse.h>

#include <type_cache/get_bool_type.h>
#include <type_cache/get_int_type.h>
#include <type_cache/get_float_type.h>
#include <type_cache/get_string_type.h>
#include <type_cache/get_list_type.h>
#include <type_cache/get_grammar_type.h>

#include <yacc/structinfo/node/struct.h>
#include <yacc/structinfo/foreach.h>

#include <type/grammar/add_field.h>

#include <type_check/build_type.h>

#include "specialize_grammar_types.h"

void specialize_grammar_types(
	struct avl_tree_t* types, // named_type*
	struct type_cache* tcache,
	struct avl_tree_t* structinfos) // named_structinfo*
{
	ENTER;
	
	avl_foreach(structinfos, ({
		void runme(void* ptr)
		{
			struct named_structinfo* nsinfo = ptr;
			
			dpvs(nsinfo->name);
			
			struct type* type = type_cache_get_grammar_type(tcache, nsinfo->name);
			
			dpv(type);
			
			struct grammar_type* gtype = (void*) type;
			
			structinfo_foreach(nsinfo->structinfo, ({
				void runme(struct structinfo_node* ele)
				{
					dpvs(ele->name);
					
					switch (ele->type)
					{
						case snt_token_scalar:
						{
							if (!ele->tokentype)
							{
								struct type* subtype = type_cache_get_string_type(tcache);
								grammar_type_add_field(gtype, ele->name, subtype);
							}
							else if (ele->tokentype->bool_)
							{
								struct type* subtype = type_cache_get_bool_type(tcache);
								grammar_type_add_field(gtype, ele->name, subtype);
							}
							else if (ele->tokentype->int_)
							{
								struct type* subtype = type_cache_get_int_type(tcache);
								grammar_type_add_field(gtype, ele->name, subtype);
							}
							else if (ele->tokentype->float_)
							{
								struct type* subtype = type_cache_get_float_type(tcache);
								grammar_type_add_field(gtype, ele->name, subtype);
							}
							else
							{
								TODO;
							}
							break;
						}
						
						case snt_token_array:
						{
							if (ele->tokentype)
							{
								TODO;
							}
							else
							{
								TODO;
							}
							break;
						}
						
						case snt_grammar_scalar:
						{
							dpvs(ele->grammar);
							
							struct type* subtype = type_cache_get_grammar_type(tcache, ele->grammar);
							
							grammar_type_add_field(gtype, ele->name, subtype);
							break;
						}
						
						case snt_grammar_array:
						{
							dpvs(ele->grammar);
							
							struct type* subtype_ele = type_cache_get_grammar_type(tcache, ele->grammar);
							
							struct type* subtype = type_cache_get_list_type(tcache, subtype_ele);
							
							grammar_type_add_field(gtype, ele->name, subtype);
							break;
						}
						
						default:
							TODO;
							break;
					}
				}
				runme;
			}));
			
			struct named_type* ntype = new_named_type(nsinfo->name, type);
			
			void* ptr222 = avl_insert(types, ntype);
			assert(ptr222);
		}
		runme;
	}));
	
	EXIT;
}





















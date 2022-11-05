
#ifndef RELEASE
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/param.h>
	#include <sys/types.h>
	#include <sys/mman.h>
	
	#include <semaphore.h>
	#include <assert.h>
	#include <stdio.h>
	#include <errno.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <ctype.h>
	#include <getopt.h>
	#include <stddef.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <string.h>
	#include <strings.h>
	#include <inttypes.h>
	#include <stdarg.h>
	#include <limits.h>
	#include <pwd.h>
	#include <time.h>
	#include <pwd.h>
	
	#include <gmp.h>
	
	struct pragma_once;
	struct tokenizer;
	struct expressionset;
	struct scope;
	struct regex;
	struct ptrset;
	struct quack;
	struct lex;
	struct structinfo;
	struct unsignedset;
	struct gegex;
	struct zebu_token;
	struct expression_list;
	struct type_cache;
	struct type;
	struct assertion;
	struct yacc_state;
	struct lex_state;
	struct stringtree;
	struct out_shared;
	struct shared;
	struct raw_assertion;
	struct gegex_transition;
	struct list_type;
	struct zebu_expression;
	struct grammar_type;
	struct expression;
	struct unresolved;
	struct zebu_primary_expression;
	struct zebu_type;
	struct value_list;
	struct parameter_list;
	struct stringset;
	struct parameter;
	struct type_inheritance;
	struct lambda_value;
	struct mpz;
	struct value;
	struct out_type;
	struct out_function;
	struct type_lookup;
	struct type_list;
	struct function_lookup;
	struct declare_queue;
	struct function_queue;
	struct set_queue;
	struct type_queue;
	struct lambda_expression;
	struct format_flags;
	struct specialize_shared;
	struct zpexpressionset;
	struct reductioninfo;
	struct zebu_tokentype;
	struct zebu_possession_expression;
	struct zebu_inclusion_expression;
	
	#include <memory/smalloc.h>
	#include <memory/srealloc.h>
	
	#include <defines/argv0.h>
	
	#include <macros/strequals.h>
	
	#include <enums/error.h>
	#include <enums/token_kind.h>
	
	#include <cmdln/verbose.h>
	
	#include <avl/alloc_tree.h>
	#include <avl/search.h>
	#include <avl/insert.h>
	#include <avl/foreach.h>
	#include <avl/clear_tree.h>
	#include <avl/free_tree.h>
	#include <avl/delete_node.h>
	#include <avl/delete.h>
	
	#include <string/struct.h>
	#include <string/new.h>
	#include <string/inc.h>
	#include <string/compare.h>
	#include <string/are_equal.h>
	#include <string/free.h>
	
	#include <set/ptr/new.h>
	#include <set/ptr/add.h>
	#include <set/ptr/get_head.h>
	#include <set/ptr/foreach.h>
	#include <set/ptr/contains.h>
	#include <set/ptr/update.h>
	#include <set/ptr/is_nonempty.h>
	#include <set/ptr/discard.h>
	#include <set/ptr/clear.h>
	#include <set/ptr/free.h>
	
	#include <set/string/new.h>
	#include <set/string/add.h>
	#include <set/string/filter.h>
	#include <set/string/foreach.h>
	#include <set/string/len.h>
	#include <set/string/is_nonempty.h>
	#include <set/string/contains.h>
	#include <set/string/free.h>
	
	#include <list/string/new.h>
	#include <list/string/append.h>
	#include <list/string/free.h>
	
	#include <stringtree/new.h>
	#include <stringtree/append_printf.h>
	#include <stringtree/append_tree.h>
	#include <stringtree/append_strndup.h>
	#include <stringtree/prepend_tree.h>
	#include <stringtree/inc.h>
	#include <stringtree/free.h>
	
	#include <heap/new.h>
	#include <heap/is_nonempty.h>
	#include <heap/push.h>
	#include <heap/pop.h>
	#include <heap/free.h>
	
	#include <quack/new.h>
	#include <quack/is_nonempty.h>
	#include <quack/append.h>
	#include <quack/len.h>
	#include <quack/pop.h>
	#include <quack/free.h>
	
	#include <type/print.h>
	
	#include <type_cache/get_type/int.h>
	#include <type_cache/get_type/list.h>
	#include <type_cache/get_type/lambda.h>
	
	#include <misc/default_sighandler.h>
#endif

#ifdef DEBUGGING
	extern __thread int debug_depth;
	
	extern void real_dpvc(const char* e, char ch);
	
	extern void real_dpvsn(const char* e, const char* s, size_t n);
	
	extern void real_dpvwsn(const char* e, const wchar_t* s, size_t n);
	
	#define TODO \
	{\
		assert(debug_depth >= 0); \
		printf("%*s""TODO: File: %s: Line: %i\n", debug_depth, "", \
			__FILE__, __LINE__);\
		fflush(stdout); \
		char buffer[100];\
		sprintf(buffer, "+%i", __LINE__);\
		if (!fork()) \
			execlp("gedit", "gedit", __FILE__, buffer, NULL);\
		assert(!"TODO"); \
	}
	
	#define CHECK \
	{\
		assert(debug_depth >= 0); \
		printf("%*s""CHECK: File: %s: Line: %i\n", debug_depth, "", \
			__FILE__, __LINE__);\
		fflush(stdout); \
		char buffer[100];\
		sprintf(buffer, "+%i", __LINE__);\
		if (!fork()) \
			execlp("gedit", "gedit", __FILE__, buffer, NULL);\
		assert(!"CHECK"); \
	}
	
	#define NOPE \
	{\
		assert(debug_depth >= 0); \
		printf("%*s""NOPE: File: %s: Line: %i\n", debug_depth, "", \
			__FILE__, __LINE__);\
		fflush(stdout); \
		char buffer[100];\
		sprintf(buffer, "+%i", __LINE__);\
		if (!fork()) \
			execlp("gedit", "gedit", __FILE__, buffer, NULL);\
		assert(!"NOPE"); \
	}
	
	#define CHECK_NTH(n) \
	{ \
		static unsigned counter = 1; \
		if (counter++ == n) \
		{ \
			CHECK; \
		} \
	} \
	
	#define HERE \
		printf("%*sHERE: File: %s: Line: %i\n", debug_depth, "", __FILE__, __LINE__);

	#define ENTER \
		assert(debug_depth >= 0); \
		printf("%*s<%s>\n", debug_depth++, "", __PRETTY_FUNCTION__);
	
	#define EXIT \
		assert(--debug_depth >= 0); \
		printf("%*s</%s>\n", debug_depth, "", __PRETTY_FUNCTION__);
	
	#define dpv(val) dprint(val)
	
	#define dpvb(b) \
		assert(debug_depth >= 0);\
		printf("%*s" #b " == %s\n", debug_depth, "", (b) ? "true" : "false");
	
	#define dputs(str) \
		assert(debug_depth >= 0);\
		printf("%*s" "%s\n", debug_depth, "", str);
	
	#define dpvc(ch) \
		real_dpvc(#ch, ch);
	
	#define dpvsn(str, _len) { \
		_Generic(str, \
			char*:          real_dpvsn (#str, ( char  *) (str), _len), \
			const char*:    real_dpvsn (#str, ( char  *) (str), _len), \
			struct string*: real_dpvsn(#str, ((struct string*) (str))->chars, ((struct string*) (str))->len), \
			wchar_t*:       real_dpvwsn(#str, (wchar_t*) (str), _len), \
			const wchar_t*: real_dpvwsn(#str, (wchar_t*) (str), _len), \
			default:        real_dpvsn (#str, (   void*) (str), _len)); \
	}
	
	#define dpvs(str) dpvsn(str, -1)
	
	#define dperror(val) { \
		assert(debug_depth >= 0); \
		printf("%*s""%s"" == %s (%s)\n", \
			debug_depth, "", \
			(const char*[]){ \
				[0] = "0", \
				[EPERM] = "EPERM", \
				[ENOENT] = "ENOENT", \
				[ESRCH] = "ESRCH", \
				[EINTR] = "EINTR", \
				[EIO] = "EIO", \
				[ENXIO] = "ENXIO", \
				[E2BIG] = "E2BIG", \
				[ENOEXEC] = "ENOEXEC", \
				[EBADF] = "EBADF", \
				[ECHILD] = "ECHILD", \
				[EAGAIN] = "EAGAIN", \
				[ENOMEM] = "ENOMEM", \
				[EACCES] = "EACCES", \
				[EFAULT] = "EFAULT", \
				[ENOTBLK] = "ENOTBLK", \
				[EBUSY] = "EBUSY", \
				[EEXIST] = "EEXIST", \
				[EXDEV] = "EXDEV", \
				[ENODEV] = "ENODEV", \
				[ENOTDIR] = "ENOTDIR", \
				[EISDIR] = "EISDIR", \
				[EINVAL] = "EINVAL", \
				[ENFILE] = "ENFILE", \
				[EMFILE] = "EMFILE", \
				[ENOTTY] = "ENOTTY", \
				[ETXTBSY] = "ETXTBSY", \
				[EFBIG] = "EFBIG", \
				[ENOSPC] = "ENOSPC", \
				[ESPIPE] = "ESPIPE", \
				[EROFS] = "EROFS", \
				[EMLINK] = "EMLINK", \
				[EPIPE] = "EPIPE", \
				[EDOM] = "EDOM", \
				[ERANGE] = "ERANGE", \
				[EHWPOISON] = "EHWPOISON", \
			}[val] ?: "???", \
			#val, strerror(val)); \
		}
	
	#define dpvo(val) { \
		assert(debug_depth >= 0);\
		printf((_Generic(val, \
			signed char:    "%*s" "%s" " == " "(signed char) 0%hho\n", \
			unsigned char:  "%*s" "%s" " == " "(unsigned char) 0%hho\n", \
			signed short:   "%*s" "%s" " == " "(signed short) 0%ho\n", \
			unsigned short: "%*s" "%s" " == " "(unsigned char) 0%ho\n", \
			signed int:     "%*s" "%s" " == " "(signed int) 0%o\n", \
			unsigned int:   "%*s" "%s" " == " "(unsigned int) 0%o\n", \
			signed long:    "%*s" "%s" " == " "(signed long) 0%lo\n", \
			unsigned long:  "%*s" "%s" " == " "(unsigned long) 0%lo\n", \
			float:          "%*s" "%s" " == " "(float) %#a\n", \
			double:         "%*s" "%s" " == " "(double) %#la\n", \
			long double:    "%*s" "%s" " == " "(long double) %#La\n", \
			default:        "%*s" "%s" " == " "(void*) %#p\n")), \
			debug_depth, "", #val, val); \
		}
	
	#define dpvx(val) { \
		assert(debug_depth >= 0); \
		printf((_Generic(val, \
			signed char:    "%*s" "%s" " == " "(signed char) 0x%hhX\n", \
			unsigned char:  "%*s" "%s" " == " "(unsigned char) 0x%hhX\n", \
			signed short:   "%*s" "%s" " == " "(signed short) 0x%hX\n", \
			unsigned short: "%*s" "%s" " == " "(unsigned char) 0x%hX\n", \
			signed int:     "%*s" "%s" " == " "(signed int) 0x%X\n", \
			unsigned int:   "%*s" "%s" " == " "(unsigned int) 0x%X\n", \
			signed long:    "%*s" "%s" " == " "(signed long) 0x%lX\n", \
			unsigned long:  "%*s" "%s" " == " "(unsigned long) 0x%lX\n", \
			float:          "%*s" "%s" " == " "(float) %#a\n", \
			double:         "%*s" "%s" " == " "(double) %#la\n", \
			long double:    "%*s" "%s" " == " "(long double) %#La\n", \
			default:        "%*s" "%s" " == " "(void*) %#p\n")), \
			debug_depth, "", #val, val); \
		}
	
	#define dprint(val) { \
		assert(debug_depth >= 0); \
		printf((_Generic((val), \
			signed char:    "%*s" "%s" " == " "(signed char) %hhi\n", \
			unsigned char:  "%*s" "%s" " == " "(unsigned char) %hhu\n", \
			signed short:   "%*s" "%s" " == " "(signed short) %hi\n", \
			unsigned short: "%*s" "%s" " == " "(unsigned short) %hu\n", \
			signed int:     "%*s" "%s" " == " "(signed int) %i\n", \
			unsigned int:   "%*s" "%s" " == " "(unsigned int) %u\n", \
			signed long:    "%*s" "%s" " == " "(signed long) %li\n", \
			unsigned long:  "%*s" "%s" " == " "(unsigned long) %lu\n", \
			long long:      "%*s" "%s" " == " "(signed long long) %llu\n", \
			float:          "%*s" "%s" " == " "(float) %f\n", \
			double:         "%*s" "%s" " == " "(double) %lf\n", \
			long double:    "%*s" "%s" " == " "(long double) %Lf\n", \
			default:        "%*s" "%s" " == " "(void*) %p\n")), \
			debug_depth, "", #val, (val)); \
		}
	
	#define ddprintf(format, ...) { \
		assert(debug_depth >= 0); \
		printf("%*s" format, debug_depth, "", ## __VA_ARGS__); \
	}
	
#else
	#define dpv(x) ;
	#define dpvb(x) ;
	#define dpvc(x) ;
	#define dpvo(x) ;
	#define dpvs(x) ;
	#define dputs(x) ;
	#define dpvx(x) ;
	#define dpvsn(_, __) ;
	#define ddprintf(...) ;
	
	#define dperror(x) ;
	
	#define ENTER
	#define EXIT
	#define HERE
	
	#define TODO assert(!"TODO");
	#define CHECK assert(!"CHECK");
	#define NOPE assert(!"NOPE");
	
#endif





































srcs += ./assertion/free.c
srcs += ./assertion/new.c
srcs += ./avl/alloc_tree.c
srcs += ./avl/avl.c
srcs += ./avl/check_balance.c
srcs += ./avl/clear_node.c
srcs += ./avl/clear_tree.c
srcs += ./avl/delete.c
srcs += ./avl/delete_node.c
srcs += ./avl/foreach.c
srcs += ./avl/free_nodes.c
srcs += ./avl/free_tree.c
srcs += ./avl/init_node.c
srcs += ./avl/init_tree.c
srcs += ./avl/insert.c
srcs += ./avl/insert_after.c
srcs += ./avl/insert_before.c
srcs += ./avl/insert_node.c
srcs += ./avl/insert_top.c
srcs += ./avl/rebalance.c
srcs += ./avl/search.c
srcs += ./avl/search_closest.c
srcs += ./avl/unlink_node.c
srcs += ./builtin/map/evaluate.c
srcs += ./cmdln/free.c
srcs += ./cmdln/process.c
srcs += ./cmdln/usage.c
srcs += ./debug.c
srcs += ./expression/call/evaluate.c
srcs += ./expression/evaluate.c
srcs += ./expression/float_math/evaluate.c
srcs += ./expression/free.c
srcs += ./expression/inc.c
srcs += ./expression/int_math/evaluate.c
srcs += ./expression/int_math/free.c
srcs += ./expression/int_math/inheritance.c
srcs += ./expression/int_math/new.c
srcs += ./expression/lambda/evaluate.c
srcs += ./expression/lambda/free.c
srcs += ./expression/lambda/new.c
srcs += ./expression/list/evaluate.c
srcs += ./expression/list/inheritance.c
srcs += ./expression/list_concat/evaluate.c
srcs += ./expression/literal/evaluate.c
srcs += ./expression/literal/free.c
srcs += ./expression/literal/inheritance.c
srcs += ./expression/literal/new.c
srcs += ./expression/new.c
srcs += ./expression/tuple/evaluate.c
srcs += ./expression/tuple_concat/evaluate.c
srcs += ./expression/variable/evaluate.c
srcs += ./expression/variable/free.c
srcs += ./expression/variable/inheritance.c
srcs += ./expression/variable/new.c
srcs += ./gegex/add_grammar_transition.c
srcs += ./gegex/add_lambda_transition.c
srcs += ./gegex/add_transition.c
srcs += ./gegex/combine_structinfos.c
srcs += ./gegex/free.c
srcs += ./gegex/grammar/free.c
srcs += ./gegex/grammar/new.c
srcs += ./gegex/new.c
srcs += ./gegex/nfa_to_dfa.c
srcs += ./gegex/simplify_dfa.c
srcs += ./gegex/transition/free.c
srcs += ./gegex/transition/new.c
srcs += ./heap/free.c
srcs += ./heap/head.c
srcs += ./heap/is_nonempty.c
srcs += ./heap/new.c
srcs += ./heap/pop.c
srcs += ./heap/push.c
srcs += ./lex/add_token.c
srcs += ./lex/free.c
srcs += ./lex/new.c
srcs += ./lex/token_to_id_node/compare.c
srcs += ./lex/token_to_id_node/free.c
srcs += ./lex/token_to_id_node/new.c
srcs += ./list/expression/append.c
srcs += ./list/expression/free.c
srcs += ./list/expression/inc.c
srcs += ./list/expression/new.c
srcs += ./list/parameter/append.c
srcs += ./list/parameter/compare.c
srcs += ./list/parameter/free.c
srcs += ./list/parameter/inc.c
srcs += ./list/parameter/is_nonempty.c
srcs += ./list/parameter/new.c
srcs += ./list/value/append.c
srcs += ./list/value/free.c
srcs += ./list/value/inc.c
srcs += ./list/value/new.c
srcs += ./main.c
srcs += ./memory/smalloc.c
srcs += ./memory/srealloc.c
srcs += ./misc/break_and_open_path.c
srcs += ./misc/sopenat.c
srcs += ./mpz/add.c
srcs += ./mpz/free.c
srcs += ./mpz/inc.c
srcs += ./mpz/multiply.c
srcs += ./mpz/new.c
srcs += ./mpz/subtract.c
srcs += ./named/expression/compare.c
srcs += ./named/expression/free.c
srcs += ./named/expression/new.c
srcs += ./named/grammar/compare.c
srcs += ./named/grammar/free.c
srcs += ./named/grammar/new.c
srcs += ./named/structinfo/compare.c
srcs += ./named/structinfo/free.c
srcs += ./named/structinfo/new.c
srcs += ./named/type/compare.c
srcs += ./named/type/free.c
srcs += ./named/type/new.c
srcs += ./named/value/compare.c
srcs += ./named/value/free.c
srcs += ./named/value/new.c
srcs += ./named/zebu_expression/compare.c
srcs += ./named/zebu_expression/free.c
srcs += ./named/zebu_expression/new.c
srcs += ./parameter/free.c
srcs += ./parameter/inc.c
srcs += ./parameter/new.c
srcs += ./parse/assertion.c
srcs += ./parse/assertion/free.c
srcs += ./parse/assertion/new.c
srcs += ./parse/charset.c
srcs += ./parse/declare.c
srcs += ./parse/driver.c
srcs += ./parse/grammar.c
srcs += ./parse/grammar/0.highest.c
srcs += ./parse/grammar/0.highest/character.c
srcs += ./parse/grammar/0.highest/name.c
srcs += ./parse/grammar/0.highest/regex.c
srcs += ./parse/grammar/0.highest/string.c
srcs += ./parse/grammar/1.postfix.c
srcs += ./parse/grammar/2.juxtaposition.c
srcs += ./parse/grammar/3.root.c
srcs += ./parse/misc/escapes.c
srcs += ./parse/parse.c
srcs += ./parse/regex.c
srcs += ./parse/skip.c
srcs += ./parse/start.c
srcs += ./parse/using.c
srcs += ./quack/append.c
srcs += ./quack/free.c
srcs += ./quack/is_nonempty.c
srcs += ./quack/new.c
srcs += ./quack/pop.c
srcs += ./quack/prepend.c
srcs += ./regex/add_lambda_transition.c
srcs += ./regex/compare_simplified.c
srcs += ./regex/free.c
srcs += ./regex/new.c
srcs += ./regex/new_from_charset.c
srcs += ./regex/new_from_string.c
srcs += ./regex/nfa_to_dfa.c
srcs += ./regex/set_kind.c
srcs += ./regex/simplify_dfa.c
srcs += ./scope/declare.c
srcs += ./scope/free.c
srcs += ./scope/lookup.c
srcs += ./scope/new.c
srcs += ./set/expression/free.c
srcs += ./set/expression/new.c
srcs += ./set/ptr/add.c
srcs += ./set/ptr/clone.c
srcs += ./set/ptr/compare.c
srcs += ./set/ptr/contains.c
srcs += ./set/ptr/discard.c
srcs += ./set/ptr/foreach.c
srcs += ./set/ptr/free.c
srcs += ./set/ptr/get_head.c
srcs += ./set/ptr/inc.c
srcs += ./set/ptr/is_nonempty.c
srcs += ./set/ptr/new.c
srcs += ./set/unsigned/add.c
srcs += ./set/unsigned/clear.c
srcs += ./set/unsigned/clone.c
srcs += ./set/unsigned/compare.c
srcs += ./set/unsigned/foreach.c
srcs += ./set/unsigned/free.c
srcs += ./set/unsigned/head.c
srcs += ./set/unsigned/inc.c
srcs += ./set/unsigned/len.c
srcs += ./set/unsigned/new.c
srcs += ./set/unsigned/to_string.c
srcs += ./set/unsigned/update.c
srcs += ./string/are_equal.c
srcs += ./string/compare.c
srcs += ./string/free.c
srcs += ./string/inc.c
srcs += ./string/new.c
srcs += ./type/bool/compare.c
srcs += ./type/bool/free.c
srcs += ./type/bool/inheritance.c
srcs += ./type/bool/new.c
srcs += ./type/compare.c
srcs += ./type/free.c
srcs += ./type/grammar/compare.c
srcs += ./type/grammar/free.c
srcs += ./type/grammar/inheritance.c
srcs += ./type/grammar/new.c
srcs += ./type/inc.c
srcs += ./type/int/compare.c
srcs += ./type/int/free.c
srcs += ./type/int/inheritance.c
srcs += ./type/int/new.c
srcs += ./type/lambda/compare.c
srcs += ./type/lambda/free.c
srcs += ./type/lambda/inheritance.c
srcs += ./type/lambda/new.c
srcs += ./type/list/compare.c
srcs += ./type/list/free.c
srcs += ./type/list/inheritance.c
srcs += ./type/list/new.c
srcs += ./type/new.c
srcs += ./type_cache/free.c
srcs += ./type_cache/get_type/bool.c
srcs += ./type_cache/get_type/char.c
srcs += ./type_cache/get_type/grammar.c
srcs += ./type_cache/get_type/int.c
srcs += ./type_cache/get_type/lambda.c
srcs += ./type_cache/get_type/list.c
srcs += ./type_cache/get_type/tuple.c
srcs += ./type_cache/new.c
srcs += ./type_cache/node/compare.c
srcs += ./type_cache/node/free.c
srcs += ./type_cache/node/new.c
srcs += ./type_check/build_type.c
srcs += ./type_check/resolve_variables.c
srcs += ./type_check/specialize/additive.c
srcs += ./type_check/specialize/and.c
srcs += ./type_check/specialize/conditional.c
srcs += ./type_check/specialize/equality.c
srcs += ./type_check/specialize/exclusive_or.c
srcs += ./type_check/specialize/exponentiation.c
srcs += ./type_check/specialize/expression.c
srcs += ./type_check/specialize/implication.c
srcs += ./type_check/specialize/inclusive_or.c
srcs += ./type_check/specialize/lambda.c
srcs += ./type_check/specialize/logical_and.c
srcs += ./type_check/specialize/logical_or.c
srcs += ./type_check/specialize/multiplicative.c
srcs += ./type_check/specialize/possession.c
srcs += ./type_check/specialize/postfix.c
srcs += ./type_check/specialize/primary.c
srcs += ./type_check/specialize/relational.c
srcs += ./type_check/specialize/shift.c
srcs += ./type_check/specialize/unary.c
srcs += ./type_check/type_check.c
srcs += ./type_check/unresolved/add.c
srcs += ./type_check/unresolved/foreach.c
srcs += ./type_check/unresolved/free.c
srcs += ./type_check/unresolved/inc.c
srcs += ./type_check/unresolved/is_nonempty.c
srcs += ./type_check/unresolved/len.c
srcs += ./type_check/unresolved/new.c
srcs += ./type_check/unresolved/node/compare.c
srcs += ./type_check/unresolved/node/free.c
srcs += ./type_check/unresolved/node/inc.c
srcs += ./type_check/unresolved/node/new.c
srcs += ./type_check/unresolved/resolve.c
srcs += ./type_check/unresolved/update.c
srcs += ./value/bool/compare.c
srcs += ./value/bool/free.c
srcs += ./value/bool/inheritance.c
srcs += ./value/bool/new.c
srcs += ./value/compare.c
srcs += ./value/free.c
srcs += ./value/inc.c
srcs += ./value/integer/compare.c
srcs += ./value/integer/free.c
srcs += ./value/integer/inheritance.c
srcs += ./value/integer/new.c
srcs += ./value/lambda/call.c
srcs += ./value/lambda/free.c
srcs += ./value/lambda/inheritance.c
srcs += ./value/lambda/new.c
srcs += ./value/list/compare.c
srcs += ./value/list/free.c
srcs += ./value/list/inheritance.c
srcs += ./value/list/new.c
srcs += ./value/new.c
srcs += ./yacc/structinfo/add_field.c
srcs += ./yacc/structinfo/compare.c
srcs += ./yacc/structinfo/free.c
srcs += ./yacc/structinfo/inc.c
srcs += ./yacc/structinfo/new.c
srcs += ./yacc/structinfo/node/compare.c
srcs += ./yacc/structinfo/node/free.c
srcs += ./yacc/structinfo/node/inc.c
srcs += ./yacc/structinfo/node/new.c
srcs += ./yacc/structinfo/update.c

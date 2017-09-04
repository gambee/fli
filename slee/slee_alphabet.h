/* slee_alphabet.h
 *
 *
 * Arithmetic-like (v3):			-, +, *, 1, 0, <, = 
 *
 *
 *
 */


#ifndef SLEE_ALPHABET		//conditional compilation for entire file
#	define SLEE_ALPHABET
#	ifdef OTHER_VERSIONS	//elifs with other optional alphabets
#	else					//default alphabet: Arithmetic-like (v3)
#		define ARITHMETIC_LIKE_V3
#		define SLEE_FALSE	'0'
#		define SLEE_TRUE	'1'
#		define SLEE_NOT		'-'
#		define SLEE_OR		'+'
#		define SLEE_AND		'*'
#		define SLEE_IF		'<'
#		define SLEE_IFF		'='
#	endif					//end of ifelse OTHER_VESIONS switch

#endif //ifndef SLEE_ALPHABET

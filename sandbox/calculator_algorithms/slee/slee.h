/* slee.h
 *
 * Max Gambee
 * Copyright 2017
 *
 * Description: This header implements a Sentential Logic Expression Evaluator
 * 		as a deterministic pushdown transducer, using the character stack 
 * 		implementation contained in fli_stack.h. All expressions passed to the
 * 		slee must be tokenized reverse polish notation style sentential logic
 * 		expressions with T/F valued literals.
 */

#ifndef SLEE_H
#	define STATE_H

#include "fli_stack.h"
#include "slee_alphabet.h"


/**********************
 * Section: Functions
 **********************/

/* Each state will have a corresponding function that acts as a 'restriction'
 * of the full transition function of the pda, (more or less; the pda being
 * implemented here is not declared in the C programming language in the way
 * the pure mathematical definition would require, for efficiency/practicality
 * reasons). These 'state' functions will be sort of piece-wise combined to 
 * form the transition function (which is technically not explicitly declared 
 * anywhere), by having each return the location of the next. 
 */

/* Transition Function 'sub-function' routine prototypes: */
	//Main
void* TRANS_q0(char (*input)(void), char *to_push);
void* TRANS_q1(char (*input)(void), char *to_push);
void* TRANS_q2(char (*input)(void), char *to_push);
	//Negation
void* TRANS_n0(char (*input)(void), char *to_push);
void* TRANS_n1(char (*input)(void), char *to_push);
void* TRANS_n2(char (*input)(void), char *to_push);
	//Conditional
void* TRANS_c0(char (*input)(void), char *to_push);
void* TRANS_c1(char (*input)(void), char *to_push);
void* TRANS_c2(char (*input)(void), char *to_push);
void* TRANS_c3(char (*input)(void), char *to_push);
void* TRANS_c4(char (*input)(void), char *to_push);
	//Biconditional
void* TRANS_b0(char (*input)(void), char *to_push);
void* TRANS_b1(char (*input)(void), char *to_push);
void* TRANS_b2(char (*input)(void), char *to_push);
void* TRANS_b3(char (*input)(void), char *to_push);
void* TRANS_b4(char (*input)(void), char *to_push);
	//Conjunction
void* TRANS_a0(char (*input)(void), char *to_push);
void* TRANS_a1(char (*input)(void), char *to_push);
void* TRANS_a2(char (*input)(void), char *to_push);
void* TRANS_a3(char (*input)(void), char *to_push);
void* TRANS_a4(char (*input)(void), char *to_push);
	//Disjunction
void* TRANS_d0(char (*input)(void), char *to_push);
void* TRANS_d1(char (*input)(void), char *to_push);
void* TRANS_d2(char (*input)(void), char *to_push);
void* TRANS_d3(char (*input)(void), char *to_push);
void* TRANS_d4(char (*input)(void), char *to_push);


int SLEE_eval(char* expr, char* result)
{
	struct STK_stack stack;
	void* (*transition)(char (*input)(void), char *to_push);
	
	STK_init(stack);
	return 0;
}
	

#endif //SLEE_H

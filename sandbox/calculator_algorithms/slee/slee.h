/* flee.h
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

#include "fli_stack.h"





int SLEE_eval(char* expr, char* result)
{
	STK_stack stack;
	STK_init(stack);

}
	


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

/********************
 * Section: Defines *
 ********************/

	//Fail States For SLEE PDA:
#define SLEE_FAIL_q0 0x00
#define SLEE_FAIL_q1 0x01
#define SLEE_FAIL_q2 0x02
#define SLEE_FAIL_n0 0x10
#define SLEE_FAIL_n1 0x11
#define SLEE_FAIL_n2 0x12
#define SLEE_FAIL_c0 0x20
#define SLEE_FAIL_c1 0x21
#define SLEE_FAIL_c2 0x22
#define SLEE_FAIL_c3 0x23
#define SLEE_FAIL_c4 0x24
#define SLEE_FAIL_b0 0x30
#define SLEE_FAIL_b1 0x31
#define SLEE_FAIL_b2 0x32
#define SLEE_FAIL_b3 0x33
#define SLEE_FAIL_b4 0x34
#define SLEE_FAIL_a0 0x40
#define SLEE_FAIL_a1 0x41
#define SLEE_FAIL_a2 0x42
#define SLEE_FAIL_a3 0x43
#define SLEE_FAIL_a4 0x44
#define SLEE_FAIL_d0 0x50
#define SLEE_FAIL_d1 0x51
#define SLEE_FAIL_d2 0x52
#define SLEE_FAIL_d3 0x53
#define SLEE_FAIL_d4 0x54

	//Fail Flags for fli_stack operations:
#define STACK_FAIL_MALLOC 0x10
#define STACK_FAIL_NILSTK 0x11
#define STACK_FAIL_EMPTY  0x12

/*****************************
 * Section: Global Variables *
 *****************************/

static char(*slee_input)(void); 
static char *slee_expr;
static struct STK_stack slee_stack;
	//fail flags:
static char fail_state;
static char fail_stack;

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

/* Inititialization Funtion(s): */

int SLEE_init(void)
{
	STK_init(slee_stack);
	slee_input = NULL;
	slee_expr = NULL;
	fail_state = 0x00;
	fail_stack = 0x00;
}

int SLEE_reinit(void)
{
	slee_input = NULL;
	slee_expr = NULL;
	fail_state = 0x00;
	fail_stack = 0x00;
	return STK_popall(&slee_stack);
}

/* Character input/output functions: */

char SLEE_next_symbol(void)
{
	if(slee_expr ? *slee_expr : 0)
		return *(slee_expr++);
	else return 0;
}

char SLEE_pop(void)
{
	char ret;
	return STK_pop(&slee_stack, &ret) ? 0 : ret;
}

int SLEE_push(char to_push)
{
	return STK_push(&slee_stack, to_push);
}



/* Transition Function 'sub-function' routine prototypes: */
	//Main
void* STATE_q0(void);
void* STATE_q1(void);
void* STATE_q2(void);
	//Negation
void* STATE_n0(void);
void* STATE_n1(void);
void* STATE_n2(void);
	//Conditional
void* STATE_c0(void);
void* STATE_c1(void);
void* STATE_c2(void);
void* STATE_c3(void);
void* STATE_c4(void);
	//Biconditional
void* STATE_b0(void);
void* STATE_b1(void);
void* STATE_b2(void);
void* STATE_b3(void);
void* STATE_b4(void);
	//Conjunction
void* STATE_a0(void);
void* STATE_a1(void);
void* STATE_a2(void);
void* STATE_a3(void);
void* STATE_a4(void);
	//Disjunction
void* STATE_d0(void);
void* STATE_d1(void);
void* STATE_d2(void);
void* STATE_d3(void);
void* STATE_d4(void);

/* Transition Function 'sub-function' routine definitions: */
	//Main
void* STATE_q0(void)
{
	switch(slee_input())
	{
		case '1':
			return (void *) STATE_q1;
		case '0':
			return (void *) STATE_q2;
		case '-':
			return (void *) STATE_n0;
		case '<':
			return (void *) STATE_c0;
		case '=':
			return (void *) STATE_b0;
		case '*':
			return (void *) STATE_a0;
		case '+':
			return (void *) STATE_d0;
		default:
			fail_state = SLEE_FAIL_q0;
			return (void *) NULL;
	}
	return NULL;
}


void* STATE_q1(void)
{
	switch(SLEE_push('1'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_q1;
	return (void *) NULL;
}


void* STATE_q2(void)
{
	switch(SLEE_push('0'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_q1;
	return (void *) NULL;
}


	//Negation
void* STATE_n0(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_n1;
		case '0':
			return (void *) STATE_n2;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00;
			break;
	}

	fail_state = SLEE_FAIL_n0;
	return (void *) NULL;
}


void* STATE_n1(void)
{
	switch(SLEE_push('0'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_n1;
	return (void *) NULL;
}


void* STATE_n2(void)
{
	switch(SLEE_push('1'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_n1;
	return (void *) NULL;
}


	//Conditional
void* STATE_c0(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_c1;
		case '0':
			return (void *) STATE_c3;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_c0;
	return (void *) NULL;
}


void* STATE_c1(void)
{
	switch(SLEE_pop())
	{
		case '1':
		//	return (void *) STATE_c2;
		case '0':
			return (void *) STATE_c2;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_c1;
	return (void *) NULL;
}


void* STATE_c2(void)
{
	switch(SLEE_push('1'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}

	fail_state = SLEE_FAIL_c2;
	return (void *) NULL;
}


void* STATE_c3(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_c4;
		case '0':
			return (void *) STATE_c2;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_c4;
	return (void *) NULL;
}


void* STATE_c4(void)
{
	switch(SLEE_push('0'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}

	fail_state = SLEE_FAIL_c4;
	return (void *) NULL;
}


	//Biconditional
void* STATE_b0(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_b1;
		case '0':
			return (void *) STATE_b2;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_b0;
	return (void *) NULL;
}


void* STATE_b1(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_b3;
		case '0':
			return (void *) STATE_b4;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_b1;
	return (void *) NULL;
}


void* STATE_b2(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_b4;
		case '0':
			return (void *) STATE_b3;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_b2;
	return (void *) NULL;
}


void* STATE_b3(void)
{
	switch(SLEE_push('1'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_b3;
	return (void *) NULL;
}


void* STATE_b4(void)
{
	switch(SLEE_push('0'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_b4;
	return (void *) NULL;
}

	//Conjunction
void* STATE_a0(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_a1;
		case '0':
			return (void *) STATE_a2;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_a0;
	return (void *) NULL;
}


void* STATE_a1(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_a3;
		case '0':
			return (void *) STATE_a4;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_a1;
	return (void *) NULL;
}


void* STATE_a2(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_a4;
		case '0':
			return (void *) STATE_a4;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_a2;
	return (void *) NULL;
}


void* STATE_a3(void)
{
	switch(SLEE_push('1'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_a3;
	return (void *) NULL;
}


void* STATE_a4(void)
{
	switch(SLEE_push('0'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_a4;
	return (void *) NULL;
}


	//Disjunction
void* STATE_d0(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_d1;
		case '0':
			return (void *) STATE_d2;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_d0;
	return (void *) NULL;
}


void* STATE_d1(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_d3;
		case '0':
			return (void *) STATE_d3;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_d1;
	return (void *) NULL;
}


void* STATE_d2(void)
{
	switch(SLEE_pop())
	{
		case '1':
			return (void *) STATE_d3;
		case '0':
			return (void *) STATE_d4;
		case 0:
			fail_stack = STACK_FAIL_EMPTY;
			break;
		default:
			fail_stack = 0x00; //Unkown stack error
			break;
	}

	fail_state = SLEE_FAIL_d2;
	return (void *) NULL;
}


void* STATE_d3(void)
{
	switch(SLEE_push('1'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_d3;
	return (void *) NULL;
}


void* STATE_d4(void)
{
	switch(SLEE_push('0'))
	{
		case 0:
			return (void *) STATE_q0;
		case -1:
			fail_stack = STACK_FAIL_MALLOC;
			break;
		case -2:
			fail_stack = STACK_FAIL_NILSTK;
			break;
		default:
			fail_stack = 0x00; //Unkown error
			break;
	}
		
	fail_state = SLEE_FAIL_d4;
	return (void *) NULL;
}


int SLEE_eval(char* expr, char* result)
{
		//locals
	void* (*cur_state)(void) = STATE_q0;

		//init of args/globals
	slee_input = SLEE_next_symbol;
	*result = 'E';

	if(expr ? (slee_expr = expr, 0) : 1)
		return -1; //expr == (nil)

	while(cur_state)
		cur_state = (void* (*)(void)) cur_state();

	SLEE_reinit();
	return 0;
}
	

#endif //SLEE_H

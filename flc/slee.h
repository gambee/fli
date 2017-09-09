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
#	define SLEE_H

#include "fli_stack.h"
#include "slee_alphabet.h"

/********************
 * Section: Defines *
 ********************/

	//Fail States For SLEE PDA:
#define SLEE_FAIL_q0 0x11
#define SLEE_FAIL_q1 0x12
#define SLEE_FAIL_q2 0x13
#define SLEE_FAIL_n0 0x21
#define SLEE_FAIL_n1 0x22
#define SLEE_FAIL_n2 0x23
#define SLEE_FAIL_c0 0x31
#define SLEE_FAIL_c1 0x32
#define SLEE_FAIL_c2 0x33
#define SLEE_FAIL_c3 0x34
#define SLEE_FAIL_c4 0x35
#define SLEE_FAIL_b0 0x41
#define SLEE_FAIL_b1 0x42
#define SLEE_FAIL_b2 0x43
#define SLEE_FAIL_b3 0x44
#define SLEE_FAIL_b4 0x45
#define SLEE_FAIL_a0 0x51
#define SLEE_FAIL_a1 0x52
#define SLEE_FAIL_a2 0x53
#define SLEE_FAIL_a3 0x54
#define SLEE_FAIL_a4 0x55
#define SLEE_FAIL_d0 0x61
#define SLEE_FAIL_d1 0x62
#define SLEE_FAIL_d2 0x63
#define SLEE_FAIL_d3 0x64
#define SLEE_FAIL_d4 0x65
#define SLEE_FAIL_f0 0x71
#define SLEE_FAIL_f1 0x72

	//Fail Flags for fli_stack operations:
#define STACK_FAIL_MALLOC 0x10
#define STACK_FAIL_NILSTK 0x11
#define STACK_FAIL_EMPTY  0x12

/*****************************
 * Section: Global Variables *
 *****************************/

static char *slee_expr;
static char slee_result;
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

void SLEE_init(void)
{
	STK_init(slee_stack);
	slee_expr = NULL;
	fail_state = 0x00;
	fail_stack = 0x00;
}

int SLEE_reinit(void)
{
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
	//Final/Success States
void* STATE_f0(void);
void* STATE_f1(void);
void* STATE_s0(void);
void* STATE_s1(void);

/* Transition Function 'sub-function' routine definitions: */
	//Main
void* STATE_q0(void)
{
	/*printf("q0 ");*/

	switch(SLEE_next_symbol())
	{
		case 0: //end of input string
			switch(SLEE_pop())
			{
				case SLEE_TRUE:
					return (void *) STATE_f0;
				case SLEE_FALSE:
					return (void *) STATE_f1;
				default:
					fail_state = SLEE_FAIL_q0;
					return (void *) NULL;
			}
		case SLEE_TRUE:
			return (void *) STATE_q1;
		case SLEE_FALSE:
			return (void *) STATE_q2;
		case SLEE_NOT:
			return (void *) STATE_n0;
		case SLEE_IF:
			return (void *) STATE_c0;
		case SLEE_IFF:
			return (void *) STATE_b0;
		case SLEE_AND:
			return (void *) STATE_a0;
		case SLEE_OR:
			return (void *) STATE_d0;
		default:
			fail_state = SLEE_FAIL_q0;
			return (void *) NULL;
	}
	fail_state = SLEE_FAIL_q0;
	return (void *) NULL;
}


void* STATE_q1(void)
{
	/*printf("q1 ");*/

	switch(SLEE_push(SLEE_TRUE))
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
	/*printf("q2 ");*/

	switch(SLEE_push(SLEE_FALSE))
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
	/*printf("n0 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_n1;
		case SLEE_FALSE:
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
	/*printf("n1 ");*/

	switch(SLEE_push(SLEE_FALSE))
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
	/*printf("n2 ");*/

	switch(SLEE_push(SLEE_TRUE))
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
	/*printf("c0 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_c1;
		case SLEE_FALSE:
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
	/*printf("c1 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
		//	return (void *) STATE_c2;
		case SLEE_FALSE:
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
	/*printf("c2 ");*/

	switch(SLEE_push(SLEE_TRUE))
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
	/*printf("c3 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_c4;
		case SLEE_FALSE:
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
	/*printf("c4 ");*/

	switch(SLEE_push(SLEE_FALSE))
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
	/*printf("b0 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_b1;
		case SLEE_FALSE:
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
	/*printf("b1 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_b3;
		case SLEE_FALSE:
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
	/*printf("b2 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_b4;
		case SLEE_FALSE:
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
	/*printf("b3 ");*/

	switch(SLEE_push(SLEE_TRUE))
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
	/*printf("b4 ");*/

	switch(SLEE_push(SLEE_FALSE))
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
	/*printf("a0 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_a1;
		case SLEE_FALSE:
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
	/*printf("a1 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_a3;
		case SLEE_FALSE:
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
	/*printf("a2 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_a4;
		case SLEE_FALSE:
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
	/*printf("a3 ");*/

	switch(SLEE_push(SLEE_TRUE))
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
	/*printf("a4 ");*/

	switch(SLEE_push(SLEE_FALSE))
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
	/*printf("d0 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_d1;
		case SLEE_FALSE:
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
	/*printf("d1 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_d3;
		case SLEE_FALSE:
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
	/*printf("d2 ");*/

	switch(SLEE_pop())
	{
		case SLEE_TRUE:
			return (void *) STATE_d3;
		case SLEE_FALSE:
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
	/*printf("d3 ");*/

	switch(SLEE_push(SLEE_TRUE))
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
	/*printf("d4 ");*/

	switch(SLEE_push(SLEE_FALSE))
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

void* STATE_f0(void)
{
	/*printf("f0 ");*/

	switch(SLEE_pop())
	{
		case 0:
			return (void *) STATE_s0;
		default:
			fail_state = SLEE_FAIL_f0;
			break;
	}

	return (void *) NULL;
}

void* STATE_f1(void)
{
	/*printf("f1 ");*/

	switch(SLEE_pop())
	{
		case 0:
			return (void *) STATE_s1;
		default:
			fail_state = SLEE_FAIL_f1;
			break;
	}

	return (void *) NULL;
}

void* STATE_s0(void)
{
	/*printf("s0 ");*/

	slee_result = SLEE_TRUE;
	return (void *) NULL;
}

void* STATE_s1(void)
{
	/*printf("s1 ");*/

	slee_result = '0';
	return (void *) NULL;
}

int SLEE_eval(char* expr, char* result)
{
	int ret;
	void* (*cur_state)(void) = STATE_q0; //initial state of pda

	if(expr ? (slee_expr = expr, 0) : 1)
		return -2; //expr == (nil)

	while(cur_state) //execute state machine transitions until 'done'
		cur_state = (void* (*)(void)) cur_state();

	if(!fail_state)
	{
		*result = slee_result;
		ret = 0;
	}
	else
	{
		*result = 'E';
		ret = -1;
	}

	SLEE_reinit();
	return ret;
}
	

#endif //SLEE_H

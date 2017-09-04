# slee.h
This header implements a sentential logic evaluator. The calling routine will construct a null-terminated string of char's,
formatted properly to represent a sentential logic expression with no variables, and pass it to the eval function, which 
then returns the resulting boolean value.The option to use different alphabets for the expressions is an intended feature. 
The expressions must be in postfix (reverse polish) notation, and the algorithms use a push-down automaton implementation 
to calculate the resulting values. This is intended to be used by FLI to evaulate literal expressions for truth tables and
the like.

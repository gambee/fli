#Formal Logic Interpreter
fli is a small, tenatively (self-) proposed project, to produce a propositional (sentential) logic interpreter/helper/prover.

###Intended Initial Features:
-A formal language and grammar for propositional logic, constructed from the ASCII alphabet.
-A lexer and parser for that formal language that generates an internal representation of well formed formulas within the logical system.
-Error reporting for poorly generated formulae.
-Print truth tables for a given set of formulae to stdout.
-Given a set of premises, the ability to query the truth value of a well formed formula for a result from 'True', 'False', or 'Independant'. (The term 'Independant' indicating that the value of the well formed formula in question cannot be uniquely determed solely by the given premises.)

###Intended Later Features:
-Implementation of rewrite rules based on internal models of the 'rules of inference'.
-Given a set of premises, the ability to query a set of valid rules of inference (at the first level, i.e. all possible inferences based on the propositions given, not the propositions/wffs that result from said inferences).
-Given a set of premises, and a wff, query if the wff is true, and if so, provide an annotated proof, as a set of inferences. 

#Question 1: Implement python functions for all logical operators:

# 1.1 AND (p and q)
def AND(p, q):
    if p == True and q == True:
        return True
    

# 1.2 OR (p or q)
def OR(p, q):
      if p == False and q == False:
       return False
       return True
# 1.3 IF (p -> q)
def IF(p, q):
    # Provide solution here
     if p == True and q == False:
       return False
       return True

# 1.4 NOT (-p)
def NOT(p):
    # Provide solution here
    if p == True:
       return False
       return True

# 1.5 IFF (p <-> q)    
def IFF (p, q):
    if (p == True and q == True) or (p == False and q == False):
       return True
       return False

# Question 2:

# Give a prefix representation of a proposition, of the form prop = ('OR', True, False)
# Write a function named evaluate, which will evaluate the proposition
# You should use the functions defined in question 1
def evaluate(formula):
    if formula[1:]:
        evaluate(formula[1:])
    if formula[0] == 'AND':
        return AND(formula[1], formula[2])
    elif formula[0] == 'OR':
        return OR(formula[1], formula[2])
    elif formula[0] == 'IF':
        return IF(formula[1], formula[2])
    elif formula[0] == 'IFF':
        return IFF(formula[1], formula[2])
    elif formula[0] == 'NOT':
        return NOT(formula[1])
# Question 3 (Challenge): Create a new version of your evaluate function, named evaluate_r, which also takes in a formula, but it is able to evaluate composite formulae, such as ('OR', ('NOT', True), ('AND', True, False))
# The example formula above is equivalent to (-True 'OR' (True 'AND' False)) in infix notation 
        
def evaluate_r(formula):
    if formula[1:]:
        evaluate_r(formula[1:])
    if formula[0] == 'AND':
        return AND(formula[1], formula[2])
    elif formula[0] == 'OR':
        return OR(formula[1], formula[2])
    elif formula[0] == 'IF':
        return IF(formula[1], formula[2])
    elif formula[0] == 'IFF':
        return IFF(formula[1], formula[2])
    elif formula[0] == 'NOT':
        return NOT(formula[1])

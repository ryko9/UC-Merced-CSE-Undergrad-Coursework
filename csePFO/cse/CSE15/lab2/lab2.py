import math

def factorial(N):
	previousTerm = N
	total = 1

	while previousTerm > 0:
		total *= previousTerm
		previousTerm -= 1

	return  total;

A = 5
B = 3
C = 8

ans = factorial(A) + factorial(B) + factorial(C)

expected = math.factorial(A) + math.factorial(B) + math.factorial(C)

print("Your answer: " + str(ans))
print("Expected answer: " + str(expected))




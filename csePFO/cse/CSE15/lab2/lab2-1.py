def cartesian_product(X, Y):
#provide your code here
	product = []
		for x in x:
			for y in y:
				product.append((x,y))
			return product

x = [1,2]
Y = ['a', 'b', 'c', 'd']

print cartesian_product(X, Y)

def power_set(X):
# provide your coode here
	result = [[]]
	for x in x:
		rest = [r + [x] for r in result]
		result.extend(rest)
	return result

print power_set(Y)